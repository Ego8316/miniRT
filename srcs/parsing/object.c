/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 17:50:13 by ego               #+#    #+#             */
/*   Updated: 2025/06/16 18:06:00 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	data->field_count++;
	args->x = 1;
	return (true);
}

static bool	get_object_attribute(t_parse_data *d, double *v, const char *a)
{
	d->field_count++;
	if (!ft_strcmp(a, "r"))
		printf("looking for reflecivity");
	*v = 0;
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
	scale_color(&o.color.coor);
	if (!get_object_attribute(data, &o.reflectivity, "r"))
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
