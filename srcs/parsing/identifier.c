/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifier.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 21:31:48 by ego               #+#    #+#             */
/*   Updated: 2025/06/19 02:08:38 by ego              ###   ########.fr       */
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
	char	id[WORD_SIZE];
	int		i;
	int		j;

	if (!get_next_word(data, id, &i))
		return (parse_errmsg(PARSE_ERR_NO_IDENTIFIER_FOUND, data, true, false));
	j = -1;
	while (g_ids[++j].string)
	{
		if (!ft_strcmp(g_ids[j].string, id))
		{
			data->id = g_ids[j].id;
			if (!check_duplicates(data))
				return (false);
			return (true);
		}
	}
	data->i = i;
	return (parse_errmsg(PARSE_ERR_UNKNOWN_IDENTIFIER, data, true, false));
}
