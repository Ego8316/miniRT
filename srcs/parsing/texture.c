/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 13:01:12 by ego               #+#    #+#             */
/*   Updated: 2025/07/03 14:53:18 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

bool	load_texture(char *word, t_color *color)
{
	char	filename[TEXTURE_PREFIX_SIZE + WORD_SIZE + TEXTURE_SUFFIX_SIZE];
	int		fd;

	ft_strlcpy(filename, TEXTURE_PREFIX, sizeof(filename));
	ft_strlcat(filename, word, sizeof(filename));
	ft_strlcat(filename, TEXTURE_SUFFIX, sizeof(filename));
	printf("texture filename: %s\n", filename);
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
