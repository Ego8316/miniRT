/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifier.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 21:31:48 by ego               #+#    #+#             */
/*   Updated: 2025/06/17 01:50:18 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static const t_dict	g_ids[] = {
{AMBIENT_ID, AMBIENT, SETTING_ID_SIZE},
{CAMERA_ID, CAMERA, SETTING_ID_SIZE},
{LIGHT_ID, LIGHT, SETTING_ID_SIZE},
{SPHERE_ID, SPHERE, OBJECT_ID_SIZE},
{PLANE_ID, PLANE, OBJECT_ID_SIZE},
{CYLINDER_ID, CYLINDER, OBJECT_ID_SIZE},
{CONE_ID, CONE, OBJECT_ID_SIZE},
{HYPERBOLOID_ID, HYPERBOLOID, OBJECT_ID_SIZE},
{PARABOLOID_ID, PARABOLOID, OBJECT_ID_SIZE},
{NULL, NONE, 0}
};

/**
 * @brief Retrieves the string representation of a given identifier enum.
 * 
 * Searches the global identifier dictionary `g_ids` for the matching `t_id`
 * enum and returns the corresponding identifier string (e.g. "A", "sp", etc.).
 * 
 * @param id Identifier enum to convert to string.
 * 
 * @return Corresponding identifier string if found, `NULL` otherwise.
 */
char	*get_id_string(t_id id)
{
	int	i;

	i = -1;
	while (g_ids[++i].string)
	{
		if (id == g_ids[i].id)
			return ((char *)g_ids[i].string);
	}
	return (NULL);
}

/**
 * @brief Checks if the identifier currently being parsed has already been
 * encountered before. If so, print the appropriate message. Otherwise, updates
 * the current parsing state.
 * 
 * @param data Parsing data.
 * 
 * @return `true` the current identifier is not a duplicate, `false` otherwise.
 */
bool	check_duplicates(t_parse_data *data)
{
	if (data->id == AMBIENT)
	{
		if (data->ambient_found)
			return (parse_errmsg(PARSE_ERR_AMBIENT_DUPLICATE, data,
					true, false));
		data->ambient_found = true;
	}
	else if (data->id == CAMERA)
	{
		if (data->camera_found)
			return (parse_errmsg(PARSE_ERR_CAMERA_DUPLICATE, data,
					true, false));
		data->camera_found = true;
	}
	return (true);
}

/**
 * @brief Parses the identifier from the current line.
 * 
 * @param data Parsing data.
 * 
 * @return `true` if it is an identifier, `false` otherwise.
 */
bool	get_identifier(t_parse_data *data)
{
	int	i;

	skip_spaces(data);
	if (!data->line[data->i])
		return (true);
	i = -1;
	while (g_ids[++i].string)
	{
		if (!ft_strncmp(g_ids[i].string, data->line + data->i, g_ids[i].len))
		{
			data->id = g_ids[i].id;
			break ;
		}
	}
	if (data->id == NONE || !ft_isspace(data->line[data->i + g_ids[i].len]))
		return (parse_errmsg(PARSE_ERR_UNKNOWN_IDENTIFIER, data, true, false));
	if (!check_duplicates(data))
		return (false);
	data->i += g_ids[i].len;
	return (true);
}
