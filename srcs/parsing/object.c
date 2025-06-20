/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 17:50:13 by ego               #+#    #+#             */
/*   Updated: 2025/06/20 14:43:03 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static const t_args	g_args[] = {
{SPHERE, {
{SP_DIAMETER_MIN, SP_DIAMETER_MAX, PARSE_ERR_BOUND_DIAMETER},
{0.0, 0.0, NULL},
{0.0, 0.0, NULL}
}},
{PLANE, {
{0.0, 0.0, NULL},
{0.0, 0.0, NULL},
{0.0, 0.0, NULL}
}},
{CYLINDER, {
{CY_DIAMETER_MIN, CY_DIAMETER_MAX, PARSE_ERR_BOUND_DIAMETER},
{CY_HEIGHT_MIN, CY_HEIGHT_MAX, PARSE_ERR_BOUND_HEIGHT},
{0.0, 0.0, NULL}
}},
{CONE, {
{CO_ANGLE_MIN, CO_ANGLE_MAX, PARSE_ERR_BOUND_ANGLE},
{0.0, 0.0, NULL},
{0.0, 0.0, NULL}
}},
{NONE, {
{0.0, 0.0, NULL},
{0.0, 0.0, NULL},
{0.0, 0.0, NULL}
}}
};

/**
 * @brief Parses and normalizes the orientation vector of an object.
 * 
 * @param data Parsing data.
 * @param vector Pointer to the vector structure to fill.
 * 
 * @return `true` if the vector was successfully parsed and normalized,
 * `false` otherwise.
 */
static bool	get_object_vector(t_parse_data *data, t_coor *vector)
{
	int	i;

	i = data->i;
	data->boundaries = (t_bound){VECT_MIN, VECT_MAX, PARSE_ERR_BOUND_VECT};
	if (!get_next_coordinate(data, vector))
		return (false);
	if (!normalize_vector(vector))
	{
		data->i = i;
		return (parse_errmsg(PARSE_ERR_NORM, data, true, false));
	}
	return (true);
}

/**
 * @brief Parses object-specific arguments such as diameter, height, angle,
 * etc. Determines which arguments are required based on the object type and
 * parses them within their defined boundaries.
 * 
 * @param data Parsing data.
 * @param args Pointer to a coordinate structure where argument values will be
 * stored.
 * @param `true` if all expected arguments are successfully parsed, `false`
 * otherwise.
 */
static bool	get_object_args(t_parse_data *data, double *args)
{
	int		i;
	int		j;

	i = -1;
	while (g_args[++i].id != NONE)
	{
		if (g_args[i].id == data->id)
		{
			j = -1;
			while (++j < MAX_ARGS)
			{
				data->boundaries = g_args[i].arg_bounds[j];
				if (data->boundaries.err
					&& !get_next_double(data, &args[j], false, true))
					return (false);
			}
		}
	}
	if (get_next_double(data, 0, false, false))
		return (parse_errmsg(PARSE_ERR_UNEXPECTED_ARGUMENT, data, true, false));
	return (true);
}

/**
 * @brief Parses optional object attributes such as reflectivity and bump
 * strength. Attributes are parsed as key-value pairs. Ensures that each
 * attribute appears only once and that its value lies within specified
 * boundaries.
 * 
 * @param d Parsing data.
 * @param obj Pointer to the object being parsed.
 * 
 * @return `true` if all attributes are parsed successfully, `false`
 * otherwise.
 */
static bool	get_object_attributes(t_parse_data *d, t_object *obj)
{
	char			attribute[WORD_SIZE];
	int				i;
	int				j;
	t_attribute		attributes[MAX_ATTRIBUTES];

	attributes[0] = (t_attribute){&obj->reflectivity, REFLECTIVITY_ID, false,
		PARSE_ERR_REFLECTIVITY_DUPLICATE,
		(t_bound){ATTR_MIN, ATTR_MAX, PARSE_ERR_BOUND_REFLECTIVITY}};
	attributes[1] = (t_attribute){&obj->bump_strength, BUMP_STRENGTH_ID, false,
		PARSE_ERR_BUMP_STRENGTH_DUPLICATE,
		(t_bound){ATTR_MIN, ATTR_MAX, PARSE_ERR_BOUND_BUMP_STRENGTH}};
	j = -1;
	while (++j < MAX_ATTRIBUTES && get_next_word(d, attribute, &i))
	{
		if (!get_attribute(d, attributes, i, attribute))
			return (false);
	}
	return (true);
}

/**
 * @brief Parses a object information from the current line and stores it in the
 * newly allocated list node.
 *
 * Sets appropriate boundary checks for each parameter:
 * @brief - Brightness ratio must be between `BRIGHTNESS_MIN` and
 * `BRIGHTNESS_MAX`.
 * @brief - Each color component (R, G, B) must be between `COLOR_MIN` and
 * `COLOR_MAX`.
 * 
 * Also gets optional attributes such as reflectivity and bump strength.
 *
 * Any violation of boundaries or extra data at the end of the line will
 * produce an appropriate error message and stop parsing. Color is scaled down
 * to a 0.0-1.0 range by dividing each component by 255.0.
 *
 * @param data  Pointer to the current parsing state.
 * @param object Pointer to a newly allocated object node.
 *
 * @return `true` on successful parsing, `false` on error.
 */
static bool	get_object(t_parse_data *data, t_object *object)
{
	t_object	o;

	data->boundaries = (t_bound){COORD_MIN, COORD_MAX, PARSE_ERR_BOUND_COORD};
	if (!get_next_coordinate(data, &o.pos))
		return (false);
	if (data->id != SPHERE && !get_object_vector(data, &o.vector))
		return (false);
	if (data->id != PLANE && !get_object_args(data, o.args))
		return (false);
	if (!get_next_object_color(data, &o.color))
		return (false);
	if (!get_object_attributes(data, &o))
		return (false);
	if (trailing_data(data))
		return (false);
	*object = o;
	return (true);
}

/**
 * @brief Allocates and initializes a object node from the current parse data,
 * then adds it to the scene.
 * 
 * @param data Parse data.
 * @param scene Pointer to the scene.
 * 
 * @return `true` if the object was successfully parsed and added, `false`
 * otherwise.
 */
bool	add_object(t_parse_data *data, t_scene *scene)
{
	t_object	*object;

	object = (t_object *)ft_calloc(1, sizeof(t_object));
	if (!object)
		return (errmsg(ERRMSG_MALLOC, 0, 0, false));
	if (!get_object(data, object))
	{
		free(object);
		return (false);
	}
	object->id = data->id;
	object->next = NULL;
	add_object_to_list(object, &scene->objects);
	return (true);
}
