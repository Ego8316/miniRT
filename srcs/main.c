/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:39:41 by ego               #+#    #+#             */
/*   Updated: 2025/07/03 14:57:58 by ego              ###   ########.fr       */
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
	const size_t	size_x = 400;
	const size_t	size_y = 400;

	ft_bzero(&scene, sizeof(t_scene));
	ft_bzero(&mlxwindow, sizeof(t_imx));
	if (!handle_argument(ac, av))
		return (print_usage());
	if (!init_scene(av[1], &scene))
		return (free_scene(&scene));
	scene.fd = close(scene.fd);
	mlxwindow.scene = &scene;
	if (!init_window(&mlxwindow, size_x, size_y))
		return (1);
	display_scene(&mlxwindow);
	return (0);
}
