/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 13:54:08 by ego               #+#    #+#             */
/*   Updated: 2025/07/03 14:56:18 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	allocate_bump(double ***bump)
{
	int	i;

	*bump = (double **)malloc(TEXTURE_HEIGHT * sizeof(double *));
	if (!*bump)
		return (false);
	i = -1;
	while (++i < TEXTURE_HEIGHT)
	{
		(*bump)[i] = (double *)malloc(TEXTURE_WIDTH * sizeof(double));
		if (!(*bump)[i])
		{
			while (--i >= 0)
				free((*bump)[i]);
			free(*bump);
			return (false);
		}
	}
	return (true);
}

static bool	fill_bump(int fd, t_color *color)
{
	t_parse_data	data;
	int				i;
	int				j;

	ft_bzero(&data, sizeof(t_parse_data));
	i = -1;
	data.boundaries = (t_bound){COLOR_MIN, COLOR_MAX, PARSE_ERR_BOUND_COLOR};
	while (++i < TEXTURE_HEIGHT)
	{
		data.i = 0;
		data.line = ft_get_next_line(fd);
		if (!data.line && errno == ENOMEM)
			return (errmsg(ERRMSG_MALLOC, 0, 0, false));
		j = -1;
		while (++j < TEXTURE_WIDTH)
		{
			if (!get_next_double(&data, &color->bump[i][j], false, true))
				return (free_str(&data.line), false);
		}
		free_str(&data.line);
	}
	return (true);
}

bool	load_bump(char *word, t_color *color)
{
	char	filename[TEXTURE_PREFIX_SIZE + WORD_SIZE + TEXTURE_SUFFIX_SIZE];
	int		fd;

	ft_strlcpy(filename, TEXTURE_PREFIX, sizeof(filename));
	ft_strlcat(filename, word, sizeof(filename));
	ft_strlcat(filename, BUMP_SUFFIX, sizeof(filename));
	printf("bump filename: %s\n", filename);
	if (!allocate_bump(&color->bump))
		return (errmsg(ERRMSG_MALLOC, 0, 0, false));
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (errmsg(word, ": ", PARSE_ERR_NO_TEXTURE, false));
	if (!fill_bump(fd, color))
		return (close(fd), false);
	close(fd);
	return (true);
}

bool	free_bump(double ***bump)
{
	int	i;

	if (*bump)
	{
		i = -1;
		while (++i < TEXTURE_HEIGHT)
			free((*bump)[i]);
		free(*bump);
		*bump = NULL;
	}
	return (false);
}
