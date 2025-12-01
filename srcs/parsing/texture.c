/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 13:01:12 by ego               #+#    #+#             */
/*   Updated: 2025/07/03 17:43:38 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Allocates a 2D color texture buffer.
 *
 * The texture is sized `TEXTURE_HEIGHT` by `TEXTURE_WIDTH`.
 *
 * @param texture Output pointer for the allocated buffer.
 *
 * @return `true` on success, `false` on allocation failure.
 */
static bool	allocate_texture(t_coor ***texture)
{
	int	i;

	*texture = (t_coor **)malloc(TEXTURE_HEIGHT * sizeof(t_coor *));
	if (!*texture)
		return (false);
	i = -1;
	while (++i < TEXTURE_HEIGHT)
	{
		(*texture)[i] = (t_coor *)malloc(TEXTURE_WIDTH * sizeof(t_coor));
		if (!(*texture)[i])
		{
			while (--i >= 0)
				free((*texture)[i]);
			free(*texture);
			return (false);
		}
	}
	return (true);
}

/**
 * @brief Fills a texture buffer by reading RGB values from a file.
 *
 * @param fd Opened file descriptor containing the texture data.
 * @param color Color structure where the texture is stored.
 *
 * @return `true` on success, `false` on parsing error.
 */
static bool	fill_texture(int fd, t_color *color)
{
	t_parse_data	data;
	int				i;
	int				j;

	ft_bzero(&data, sizeof(t_parse_data));
	i = -1;
	while (++i < TEXTURE_HEIGHT)
	{
		data.i = 0;
		data.line = ft_get_next_line(fd);
		if (!data.line && errno == ENOMEM)
			return (errmsg(ERRMSG_MALLOC, 0, 0, false));
		j = -1;
		while (++j < TEXTURE_WIDTH)
		{
			if (!get_next_color(&data, &color->texture[i][j]))
				return (free_str(&data.line), false);
		}
		free_str(&data.line);
	}
	return (true);
}

/**
 * @brief Loads a texture file into the given color structure.
 *
 * The filename is built from the provided `word` with a fixed prefix/suffix.
 *
 * @param word Texture base name.
 * @param color Color structure to populate.
 *
 * @return `true` on success, `false` otherwise.
 */
bool	load_texture(char *word, t_color *color)
{
	char	filename[TEXTURE_PREFIX_SIZE + WORD_SIZE + TEXTURE_SUFFIX_SIZE];
	int		fd;

	ft_strlcpy(filename, TEXTURE_PREFIX, sizeof(filename));
	ft_strlcat(filename, word, sizeof(filename));
	ft_strlcat(filename, TEXTURE_SUFFIX, sizeof(filename));
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (errmsg(word, ": ", PARSE_ERR_NO_TEXTURE, false));
	if (!allocate_texture(&color->texture))
		return (close(fd), errmsg(ERRMSG_MALLOC, 0, 0, false));
	if (!fill_texture(fd, color))
		return (close(fd), false);
	close(fd);
	return (true);
}

/**
 * @brief Frees a texture buffer.
 *
 * @param texture Pointer to the texture pointer to free.
 *
 * @return Always returns `false` for convenient chaining.
 */
bool	free_texture(t_coor ***texture)
{
	int	i;

	if (*texture)
	{
		i = -1;
		while (++i < TEXTURE_HEIGHT)
			free((*texture)[i]);
		free(*texture);
		*texture = NULL;
	}
	return (false);
}
