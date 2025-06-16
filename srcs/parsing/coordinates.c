/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinates.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 01:38:38 by ego               #+#    #+#             */
/*   Updated: 2025/06/16 06:04:47 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Parses next double from the current position in the current line.
 * 
 * @param data Current parsing state.
 * @param value Pointer to the double where the parsed value will be stored.
 * @param expect_comma If `true`, expects a comma immediately after the double.
 */
bool	get_next_double(t_parse_data *data, double *value, bool expect_comma)
{
	char	*end;
	double	result;

	skip_spaces(data);
	result = ft_strtod(data->line + data->i, &end);
	if (end == data->line + data->i)
		return (parse_errmsg(PARSE_ERR_EXPECTED_DOUBLE, data));
	*value = result;
	if (*value < data->boundaries.min || *value > data->boundaries.max)
		return (parse_errmsg(data->boundaries.err, data));
	data->i += end - (data->line + data->i);
	if (*end == ',' && !expect_comma)
		return (parse_errmsg(PARSE_ERR_UNEXPECTED_COMMA, data));
	if (*end != ',' && expect_comma)
		return (parse_errmsg(PARSE_ERR_EXPECTED_COMMA, data));
	if (*end && !ft_isspace(*end) && !expect_comma)
		return (parse_errmsg(PARSE_ERR_EXPECTED_DOUBLE, data));
	if (*end)
		data->i++;
	return (true);
}

/**
 * @brief Parses the next three doubles from the current position in the line
 * as coordinates (x,y,z), expecting nothing but one comma between the values.
 * 
 * @param data Current parsing state.
 * @param coor Pointer to the coordinate where parsed values will be stored.
 * 
 * @return `true` if all three doubles were successfully parsed with correct
 * commas, `false` if a parsing error occurred.
 */
bool	get_next_coordinate(t_parse_data *data, t_coor *coor)
{
	skip_spaces(data);
	if (!get_next_double(data, &coor->x, true))
		return (false);
	if (!get_next_double(data, &coor->y, true))
		return (false);
	if (!get_next_double(data, &coor->z, false))
		return (false);
	return (true);
}

/**
 * @brief Parses next integer from the current position in the current line. It
 * is then casted into a double.
 * 
 * @param data Current parsing state.
 * @param value Pointer to the double where the parsed value will be stored.
 * @param expect_comma If `true`, expects a comma immediately after the
 * integer.
 */
bool	get_next_integer(t_parse_data *data, double *value, bool expect_comma)
{
	char	*end;
	long	result;

	skip_spaces(data);
	result = ft_strtol(data->line + data->i, &end, 10);
	if (end == data->line + data->i)
		return (parse_errmsg(PARSE_ERR_EXPECTED_INTEGER, data));
	*value = (double)result;
	if (*end && !ft_isspace(*end) && !expect_comma)
		return (parse_errmsg(PARSE_ERR_EXPECTED_INTEGER, data));
	if (*value < data->boundaries.min || *value > data->boundaries.max)
		return (parse_errmsg(data->boundaries.err, data));
	data->i += end - (data->line + data->i);
	if (*end == ',' && !expect_comma)
		return (parse_errmsg(PARSE_ERR_UNEXPECTED_COMMA, data));
	if (*end != ',' && expect_comma)
		return (parse_errmsg(PARSE_ERR_EXPECTED_COMMA, data));
	if (*end)
		data->i++;
	return (true);
}

/**
 * @brief Parses the next three integers from the current position in the line
 * as color (R,G,B), expecting nothing but one comma between the values.
 * Ensures each value is in the right range 0-255.
 * 
 * @param data Current parsing state.
 * @param coor Pointer to the coordinate where parsed values will be stored.
 * 
 * @return `true` if all three integers were successfully parsed with correct
 * commas and valid ranges, `false` if a parsing error occurred.
 */
bool	get_next_color(t_parse_data *data, t_coor *coor)
{
	skip_spaces(data);
	if (!get_next_integer(data, &coor->x, true))
		return (false);
	if (!get_next_integer(data, &coor->y, true))
		return (false);
	if (!get_next_integer(data, &coor->z, false))
		return (false);
	return (true);
}

/**
 * @brief Parses the next object color from the current position in the line.
 * Supports two types of color specifications: either a literal string
 * "checkerboard" (case-sensitive), indicating the object uses a checkerboard
 * pattern, or a standard RGB color triplet parsed via `get_next_color`.
 * 
 * @param data Current parsing state.
 * @param color Pointer to a the color where the parsed color or pattern info
 * will be stored.
 * 
 * @return `true` if a valid color or checkerboard pattern was successfully
 * parsed, `false` otherwise.
 */
bool	get_next_object_color(t_parse_data *data, t_color *color)
{
	skip_spaces(data);
	if (ft_isalpha(data->line[data->i]))
	{
		if (!ft_strncmp(data->line + data->i, CHECKERBOARD, CHECKERBOARD_SIZE)
			&& (ft_isspace(data->line[data->i + CHECKERBOARD_SIZE])
				|| !data->line[data->i + CHECKERBOARD_SIZE]))
		{
			data->i += CHECKERBOARD_SIZE;
			color->checkerboard = true;
			return (true);
		}
		else
			return (parse_errmsg(PARSE_ERR_INVALID_COLOR, data));
	}
	else
	{
		color->checkerboard = false;
		return (get_next_color(data, &color->coor));
	}
}
