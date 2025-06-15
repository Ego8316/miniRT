/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 14:57:42 by ego               #+#    #+#             */
/*   Updated: 2025/06/15 17:00:47 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <math.h>
# include <stdbool.h>
# include "macros.h"
# include "../lib/libft/libft.h"
# include "../lib/mlx/mlx.h"

// Main data structure

typedef struct s_scene
{
	int		fd;
}	t_scene;

// Parsing

bool	handle_argument(int ac, char **av);

// Utils

int		print_usage(void);
bool	errmsg(char *s1, char *s2, char *s3, bool status);

// Debug

void	print_scene(t_scene *s);

#endif