/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 05:37:17 by ego               #+#    #+#             */
/*   Updated: 2025/06/16 05:56:24 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Parses a light information from the current line and stores it in the
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
 * @param light Pointer to a newly allocated light node.
 *
 * @return `true` on successful parsing, `false` on error.
 */
static bool	get_light(t_parse_data *data, t_light *light)
{
	t_light	l;

	data->boundaries = (t_bound){COORD_MIN, COORD_MAX, PARSE_ERR_BOUND_COORD};
	if (!get_next_coordinate(data, &l.pos))
		return (false);
	data->boundaries = (t_bound){BRIGHTNESS_MIN, BRIGHTNESS_MAX,
		PARSE_ERR_BOUND_BRIGHTNESS};
	if (!get_next_double(data, &l.brightness, false))
		return (false);
	data->boundaries = (t_bound){COLOR_MIN, COLOR_MAX, PARSE_ERR_BOUND_COLOR};
	if (!get_next_color(data, &l.color))
		return (false);
	scale_color(&l.color);
	skip_spaces(data);
	if (data->line[data->i])
		return (parse_errmsg(PARSE_ERR_EXTRA_DATA, data));
	*light = l;
	return (true);
}

/**
 * @brief Adds a new light to the end of a linked list of lights. If the list
 * is empty, the new light becomes the head.
 * 
 * @param new New light to add.
 * @param lights Pointer to the head of the lights list.
 */
static void	add_light_to_list(t_light *new, t_light **lights)
{
	t_light	*l;

	if (!*lights)
	{
		*lights = new;
		return ;
	}
	l = *lights;
	while (l->next)
		l = l->next;
	l->next = new;
	return ;
}

/**
 * @brief Allocates and initializes a light node from the current parse data,
 * then adds it to the scene.
 * 
 * @param data Parse data.
 * @param scene Pointer to the scene.
 * 
 * @return `true` if the light was successfully parsed and added, `false`
 * otherwise.
 */
bool	add_light(t_parse_data *data, t_scene *scene)
{
	t_light	*light;

	light = (t_light *)ft_calloc(1, sizeof(t_light));
	if (!light)
		return (errmsg(ERRMSG_MALLOC, 0, 0, false));
	if (!get_light(data, light))
	{
		free(light);
		return (false);
	}
	light->next = NULL;
	add_light_to_list(light, &scene->lights);
	return (true);
}
