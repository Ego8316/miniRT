/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinates.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 01:38:38 by ego               #+#    #+#             */
/*   Updated: 2025/06/19 02:09:37 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Parses next double from the current position in the current line with
 * boundary checking. Can also be used in silent mode (`verb` set to `false`)
 * to check if a valid double exists at the current position without actually
 * printing error messages.
 * 
 * @param d Current parsing state.
 * @param value Pointer to the double where the parsed value will be stored.
 * @param comma If `true`, expects a comma immediately after the double.
 * @param verb Whether the parsing error message should actually be printed.
 */
bool	get_next_double(t_parse_data *d, double *v, bool comma, bool verb)
{
	char	*end;
	double	result;

	skip_spaces(d);
	result = ft_strtod(d->line + d->i, &end);
	if (end == d->line + d->i)
		return (parse_errmsg(PARSE_ERR_EXPECTED_DOUBLE, d, verb, false));
	if (v)
	{
		*v = result;
		if (*v < d->boundaries.min || *v > d->boundaries.max)
			return (parse_errmsg(d->boundaries.err, d, verb, true));
		d->i += end - (d->line + d->i);
	}
	if (*end == ',' && !comma)
		return (parse_errmsg(PARSE_ERR_UNEXPECTED_COMMA, d, verb, false));
	if (*end != ',' && comma)
		return (parse_errmsg(PARSE_ERR_EXPECTED_COMMA, d, verb, false));
	if (*end && !ft_isspace(*end) && !comma)
		return (parse_errmsg(PARSE_ERR_EXPECTED_DOUBLE, d, verb, false));
	if (*end && v)
		d->i++;
	return (true);
}

/**
 * @brief Parses the next three doubles from the current position in the line
 * as coordinates (x,y,z), expecting exactly one comma between the values.
 * 
 * @param data Parsing data.
 * @param coor Pointer to the coordinate where parsed values will be stored.
 * 
 * @return `true` if all three doubles were successfully parsed with correct
 * commas, `false` if a parsing error occurred.
 */
bool	get_next_coordinate(t_parse_data *data, t_coor *coor)
{
	skip_spaces(data);
	if (!get_next_double(data, &coor->x, true, true))
		return (false);
	if (!get_next_double(data, &coor->y, true, true))
		return (false);
	if (!get_next_double(data, &coor->z, false, true))
		return (false);
	return (true);
}

/**
 * @brief Parses next integer from the current position in the current line,
 * then casts it into a double.
 * 
 * @param data Parsing data.
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
		return (parse_errmsg(PARSE_ERR_EXPECTED_INTEGER, data, true, false));
	*value = (double)result;
	if (*end && !ft_isspace(*end) && !expect_comma)
		return (parse_errmsg(PARSE_ERR_EXPECTED_INTEGER, data, true, false));
	if (*value < data->boundaries.min || *value > data->boundaries.max)
		return (parse_errmsg(data->boundaries.err, data, true, true));
	data->i += end - (data->line + data->i);
	if (*end == ',' && !expect_comma)
		return (parse_errmsg(PARSE_ERR_UNEXPECTED_COMMA, data, true, false));
	if (*end != ',' && expect_comma)
		return (parse_errmsg(PARSE_ERR_EXPECTED_COMMA, data, true, false));
	if (*end)
		data->i++;
	return (true);
}

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
			return (parse_errmsg(PARSE_ERR_INVALID_COLOR, data, true, false));
	}
	else
	{
		color->checkerboard = false;
		return (get_next_color(data, &color->coor));
	}
}
