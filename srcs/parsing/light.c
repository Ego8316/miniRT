/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 05:37:17 by ego               #+#    #+#             */
/*   Updated: 2025/06/16 19:09:57 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Parses light information from the current line and stores it in a
 * newly allocated light node.
 *
 * Extracts and validates the light's position, brightness, and color from the
 * current line. Boundary checks are applied to ensure:
 * 
 * @brief - Position coordinates are within [COORD_MIN, COORD_MAX].
 * @brief - Brightness ratio is within [BRIGHTNESS_MIN, BRIGHTNESS_MAX].
 * @brief - Each RGB color component is within [COLOR_MIN, COLOR_MAX].
 *
 * The RGB color values are scaled down to the range [0.0, 1.0] by dividing
 * each component by 255.0.
 *
 * If any parameter fails validation or extra data remains in the line,
 * an error message is printed and parsing stops.
 *
 * @param data Parsing data.
 * @param light Newly allocated light node.
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
	if (!get_next_double(data, &l.brightness, false, true))
		return (false);
	data->boundaries = (t_bound){COLOR_MIN, COLOR_MAX, PARSE_ERR_BOUND_COLOR};
	if (!get_next_color(data, &l.color))
		return (false);
	if (trailing_data(data))
		return (false);
	*light = l;
	return (true);
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
