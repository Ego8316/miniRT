/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 13:15:43 by vviterbo          #+#    #+#             */
/*   Updated: 2025/06/24 15:52:37 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	initwindow(t_imx *window, size_t size_x, size_t size_y);
void	display_scene(t_scene scene, t_imx *window);
void	project_scene(t_scene, t_imx *window);

void	initwindow(t_imx *window, size_t size_x, size_t size_y)
{
	window->img = ft_calloca(1, sizeof(t_imgdata));
	window->size = ft_initcoor((double)size_x, (double)size_y, 0);
	window->mlx = mlx_init();
	window->img = mlx_new_image(window->mlx, size_x, size_y);
	window->win = mlx_new_window(window->mlx, size_x, size_y, "miniRT");
	window->img->addr = mlx_get_data_addr(window->img->img, &window->img->bits_per_pixel,
			&window->img->line_length, &window->img->endian);
	return ;
}


void	display_scene(t_scene scene, t_imx *window)
{
	project_scene(scene, window);
	mlx_put_image_to_window(window->mlx, window->win, window->img, 0, 0);
	mlx_hook(window->win, 17, 0, free_win, window);
	mlx_loop(window->mlx);
}

void	project_scene(t_scene scene, t_imx *window)
{
	t_view	viewbase;
	t_ray	view;
	t_coor	curr_pxl;
	t_inter	first_inter;
	t_color	color;

	curr_pxl.x = 0;
	viewbase = ft_init_view(scene, window->size);
	while (curr_pxl.x < window->size.x)
	{
		curr_pxl.y = 0;
		while (curr_pxl.y < window->size.y)
		{
			view.orig = scene.camera.vector.orig;
			view.dir = get_viewdir(viewbase, curr_pxl, window->size);
			first_inter = get_first_inter(scene, view);
			color = get_inter_color(scene, first_inter);
			set_pixel(window, curr_pxl, color);
			curr_pxl.y++;
		}
		curr_pxl.x++;
	}
	return ;
}