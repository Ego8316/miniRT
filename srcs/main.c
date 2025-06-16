/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:39:41 by ego               #+#    #+#             */
/*   Updated: 2025/06/16 06:02:32 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int ac, char **av)
{
	t_scene	scene;

	ft_memset(&scene, 0, sizeof(t_scene));
	if (!handle_argument(ac, av))
		return (print_usage());
	if (!parse_file(av[1], &scene))
		return (free_scene(&scene));
	print_scene(&scene);
	free_scene(&scene);
	return (0);
}
