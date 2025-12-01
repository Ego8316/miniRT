/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 19:19:51 by ego               #+#    #+#             */
/*   Updated: 2025/07/03 14:00:57 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Parses the next three integers from the current position in the line
 * as color (R,G,B), expecting nothing but one comma between the values.
 * Ensures each value is in the valid range 0-255.
 * 
 * @param data Parsing data.
 * @param coor Pointer to the coordinate where parsed values will be stored.
 * 
 * @return `true` if all three integers were successfully parsed with correct
 * commas and valid ranges, `false` if a parsing error occurred.
 */
bool	get_next_color(t_parse_data *data, t_coor *coor)
{
	data->boundaries = (t_bound){COLOR_MIN, COLOR_MAX, PARSE_ERR_BOUND_COLOR};
	skip_spaces(data);
	if (!get_next_integer(data, &coor->x, true))
		return (false);
	if (!get_next_integer(data, &coor->y, true))
		return (false);
	if (!get_next_integer(data, &coor->z, false))
		return (false);
	scale_color(coor);
	return (true);
}

/**
 * @brief Parses the next object color from the current position in the line.
 * Supports two types of color specifications: either a literal string
 * "checkerboard" (case-sensitive), indicating the object uses a checkerboard
 * pattern, or a standard RGB color triplet parsed via `get_next_color`.
 * 
 * @param data Parsing data.
 * @param color Pointer to the color where the parsed color or pattern info
 * will be stored.
 * 
 * @return `true` if a valid color or checkerboard pattern was successfully
 * parsed, `false` otherwise.
 */
bool	get_next_object_color(t_parse_data *data, t_color *color)
{
	int		word_start;
	char	word[WORD_SIZE];

	if (!get_next_word(data, word, &word_start))
		return (get_next_color(data, &color->coor));
	if (!ft_strcmp(word, CHECKERBOARD))
	{
		color->checkerboard = true;
		return (true);
	}
	color->textured = true;
	if (!load_texture(word, color) || !load_bump(word, color))
		return (false);
	return (true);
}
