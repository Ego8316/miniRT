/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:39:41 by ego               #+#    #+#             */
/*   Updated: 2025/06/26 19:27:56 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Displays the usage help message and returns 1.
 * 
 * @return 1.
 */
static int	print_usage(void)
{
	printf("%s%s%s\n", COLOR_B, USAGE_MSG, C_RESET);
	return (1);
}

int	main(int ac, char **av)
{
	t_scene			scene;
	t_imx			mlxwindow;
	const size_t	size_x = 1000;
	const size_t	size_y = 1000;

	ft_memset(&scene, 0, sizeof(t_scene));
	if (!handle_argument(ac, av))
		return (print_usage());
	if (!init_scene(av[1], &scene))
		return (free_scene(&scene));
	print_scene(&scene);
	if (!init_window(&mlxwindow, size_x, size_y))
		return (free_scene(&scene));
	display_scene(scene, &mlxwindow);
	free_scene(&scene);
	return (0);
}
