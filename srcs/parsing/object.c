/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 17:50:13 by ego               #+#    #+#             */
/*   Updated: 2025/06/16 19:32:58 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static const t_obj_args	g_obj_args[] = {
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
{PARABOLOID, {
{PA_SPREAD_MIN, PA_SPREAD_MAX, PARSE_ERR_BOUND_SPREAD},
{0.0, 0.0, NULL},
{0.0, 0.0, NULL}
}},
{HYPERBOLOID, {
{HY_RADIAL_MIN, HY_RADIAL_MAX, PARSE_ERR_BOUND_RADIAL},
{HY_VERTICAL_MIN, HY_VERTICAL_MAX, PARSE_ERR_BOUND_VERTICAL},
{0.0, 0.0, NULL}
}},
{NONE, {
{0.0, 0.0, NULL},
{0.0, 0.0, NULL},
{0.0, 0.0, NULL}
}}
};

static bool	get_object_vector(t_parse_data *data, t_coor *vector)
{
	int	i;

	i = data->i;
	data->boundaries = (t_bound){VECT_MIN, VECT_MAX, PARSE_ERR_BOUND_VECT};
	if (!get_next_coordinate(data, vector))
		return (false);
	if (data->id != SPHERE && !normalize_vector(vector))
	{
		data->i = i;
		return (parse_errmsg(PARSE_ERR_NORM, data, true, false));
	}
	return (true);
}

static bool	get_object_args(t_parse_data *data, t_coor *args)
{
	int		i;
	int		j;
	double	*components[3];

	components[0] = &args->x;
	components[1] = &args->y;
	components[2] = &args->z;
	i = -1;
	while (g_obj_args[++i].id != NONE)
	{
		if (g_obj_args[i].id == data->id)
		{
			j = -1;
			while (++j < 3)
			{
				data->boundaries = g_obj_args[i].arg_bounds[j];
				if (data->boundaries.err
					&& !get_next_double(data, components[j], false, true))
					return (false);
			}
		}
	}
	if (get_next_double(data, 0, false, false))
		return (parse_errmsg(PARSE_ERR_UNEXPECTED_ARGUMENT, data, true, false));
	return (true);
}

// static bool	get_object_attributes(t_parse_data *d, t_object *obj)
// {
// 	char			next_word[2];
// 	t_obj_attribute	attributes[2];

// 	attributes[0] = (t_obj_attribute){&obj->reflectivity, "r", PARSE_ERR_BOUND_REFLECTIVITY};
// 	attributes[1] = (t_obj_attribute){&obj->bump_strength, "b", PARSE_ERR_BOUND_REFLECTIVITY};
// 	skip_spaces(d);
// 	next_word[0] = d->line[d->i];
// 	next_word[1] = d->line[d->i + 1];
// 	if (!ft_strcmp(a, "r"))
// 		printf("looking for reflecivity");
// 	*v = 0;
// 	return (true);
// }

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
	if (data->id != PLANE && !get_object_args(data, &o.args))
		return (false);
	if (!get_next_object_color(data, &o.color))
		return (false);
	// if (!get_object_attribute(data, &o.reflectivity, "r"))
	// 	return (false);
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
