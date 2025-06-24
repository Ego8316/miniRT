/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:39:41 by ego               #+#    #+#             */
/*   Updated: 2025/06/24 16:55:31 by vviterbo         ###   ########.fr       */
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
	const size_t	size_x = 900;
	const size_t	size_y = 900;

	ft_memset(&scene, 0, sizeof(t_scene));
	if (ac == 2 && !ft_strcmp(av[1], "test"))
	{
		test_intersections();
		return (0);
	}
	if (!handle_argument(ac, av))
		return (print_usage());
	if (!init_scene(av[1], &scene))
		return (free_scene(&scene));
	print_scene(&scene);
	init_window(&mlxwindow, size_x, size_y);
	display_scene(scene, &mlxwindow);
	free_scene(&scene);
	return (0);
}
