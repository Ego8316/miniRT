/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 19:01:56 by ego               #+#    #+#             */
/*   Updated: 2025/06/19 01:47:52 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Parses the ambient light information from the current line and stores
 * it in the scene's ambient light field.
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
 * @param scene Pointer to the scene structure where the parsed ambient light
 * data will be stored.
 *
 * @return `true` on successful parsing, `false` on error.
 */
static bool	get_ambient_light(t_parse_data *data, t_scene *scene)
{
	t_ambient	a;

	data->boundaries = (t_bound){BRIGHTNESS_MIN,
		BRIGHTNESS_MAX, PARSE_ERR_BOUND_BRIGHTNESS};
	if (!get_next_double(data, &a.ratio, false, true))
		return (false);
	skip_spaces(data);
	if (!get_next_color(data, &a.color))
		return (false);
	if (trailing_data(data))
		return (false);
	scene->ambient = a;
	return (true);
}

/**
 * @brief Parses the camera data from the current line and stores it in the
 * scene's camera field.
 *
 * Sets appropriate boundary checks:
 * @brief - Position coordinates must be between `COORD_MIN` and `COORD_MAX`.
 * @brief  - Direction vector components must be between `VECT_MIN` and
 * `VECT_MAX`.
 * @brief - The direction vector must not be a zero vector (norm check).
 * @brief - FOV must be between `FOV_MIN` and `FOV_MAX`.
 *
 * If normalization of the direction vector fails (norm zero), an error is
 * returned. Any extra data found after expected values will also cause an
 * error.
 *
 * @param data  Pointer to the current parsing state.
 * @param scene Pointer to the scene structure where the parsed camera
 *              data will be stored.
 *
 * @return `true` on successful parsing, `false` on error.
 */
static bool	get_camera(t_parse_data *data, t_scene *scene)
{
	int			i;
	t_camera	c;

	data->boundaries = (t_bound){COORD_MIN, COORD_MAX, PARSE_ERR_BOUND_COORD};
	if (!get_next_coordinate(data, &c.vector.orig))
		return (false);
	i = data->i;
	data->boundaries = (t_bound){VECT_MIN, VECT_MAX, PARSE_ERR_BOUND_VECT};
	if (!get_next_coordinate(data, &c.vector.dir))
		return (false);
	if (!normalize_vector(&c.vector.dir))
	{
		data->i = i;
		return (parse_errmsg(PARSE_ERR_NORM, data, true, false));
	}
	data->boundaries = (t_bound){FOV_MIN, FOV_MAX, PARSE_ERR_BOUND_FOV};
	if (!get_next_integer(data, &c.fov, false))
		return (false);
	if (trailing_data(data))
		return (false);
	scene->camera = c;
	return (true);
}

/**
 * @brief Parses a single line from the scene file based on the identified
 * object. Uses the identifier parsed from the line to determine which parsing
 * delegate function to call.
 * 
 * @param Parsing data.
 * @param Pointer to the scene structure.
 * 
 * @return `true` on success, `false` otherwise.
 */
static bool	parse_line(t_parse_data *data, t_scene *scene)
{
	if (!get_identifier(data))
		return (false);
	if (data->id == NONE)
		return (true);
	data->verbose = false;
	if (data->id == AMBIENT && !get_ambient_light(data, scene))
		return (false);
	if (data->id == CAMERA && !get_camera(data, scene))
		return (false);
	if (data->id == LIGHT && !add_light(data, scene))
		return (false);
	data->verbose = true;
	if (data->id > LIGHT && !add_object(data, scene))
		return (false);
	return (true);
}

/**
 * @brief Builds up the scene structure from the filename.
 * Sets up all global fields of the given data structure to their initial
 * values before parsing the file.
 * 
 * @return `true` if everything goes fine,`false` otherwise.
 */
static bool	parse_file(t_parse_data *data, t_scene *s)
{
	data->ambient_found = false;
	data->camera_found = false;
	data->line_number = -1;
	while (true)
	{
		++data->line_number;
		data->line = ft_get_next_line(s->fd);
		if (!data->line && errno == ENOMEM)
			return (errmsg(ERRMSG_MALLOC, 0, 0, false));
		if (!data->line)
			break ;
		data->i = 0;
		data->id = NONE;
		if (!stristype(data->line, ft_isspace) && !parse_line(data, s))
			return (free_str(&data->line));
		free_str(&data->line);
	}
	return (true);
}

/**
 * @brief Initializes the scene structure by parsing the specified scene file.
 * 
 * Initializes the parsing data, opens the provided scene file and delegates
 * the file parsing to `parse_file`. After parsing, ensures there is a camera
 * and an ambient light.
 * 
 * @param filename Path to the scene description file.
 * @param s Pointer to the scene structure.
 * 
 * @return `true` if the scene was successfully initialized and parsed, `false`
 * otherwise.
 */
bool	init_scene(char *filename, t_scene *s)
{
	t_parse_data	data;

	ft_memset(&data, 0, sizeof(t_parse_data));
	s->fd = open(filename, O_RDONLY);
	if (s->fd < 0)
		return (errmsg(ERRMSG_MALLOC, 0, 0, false));
	s->filename = filename;
	if (!parse_file(&data, s))
		return (false);
	if (!data.ambient_found && !data.camera_found)
		return (parse_errmsg(PARSE_ERR_BOTH_MISSING, 0, true, false));
	if (!data.ambient_found)
		return (parse_errmsg(PARSE_ERR_AMBIENT_MISSING, 0, true, false));
	if (!data.camera_found)
		return (parse_errmsg(PARSE_ERR_CAMERA_MISSING, 0, true, false));
	return (true);
}
