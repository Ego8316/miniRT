/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 13:15:43 by vviterbo          #+#    #+#             */
/*   Updated: 2025/06/25 17:16:46 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	init_window(t_imx *window, size_t size_x, size_t size_y);
void	display_scene(t_scene scene, t_imx *window);
void	project_scene(t_scene, t_imx *window);
int		key_hook(int keycode, t_imx *data);

bool	init_window(t_imx *window, size_t size_x, size_t size_y)
{
	window->img = (t_imgdata *)ft_calloc(1, sizeof(t_imgdata));
	if (!window->img)
		return (errmsg(ERRMSG_MALLOC, 0, 0, false));
	window->size = ft_initcoor((double)size_x, (double)size_y, 0);
	window->mlx = mlx_init();
	if (!window->mlx)
		return (free_win(window), errmsg(ERRMSG_MLX_INIT, 0, 0, false));
	window->img->img = mlx_new_image(window->mlx, size_x, size_y);
	if (!window->img->img)
		return (free_win(window), errmsg(ERRMSG_MLX_IMG, 0, 0, false));
	window->win = mlx_new_window(window->mlx, size_x, size_y, NAME);
	if (!window->win)
		return (free_win(window), errmsg(ERRMSG_MLX_WIN, 0, 0, false));
	window->img->addr = mlx_get_data_addr(window->img->img,
			&window->img->bits_per_pixel, &window->img->line_length,
			&window->img->endian);
	return (true);
}

void	display_scene(t_scene scene, t_imx *window)
{
	project_scene(scene, window);
	mlx_put_image_to_window(window->mlx, window->win, window->img->img, 0, 0);
	mlx_hook(window->win, 17, 0, free_win, window);
	mlx_key_hook(window->win, key_hook, window);
	mlx_loop(window->mlx);
}

int	key_hook(int keycode, t_imx *data)
{
	if (keycode == ESC)
		free_win(data);
	return (0);
}

/**
 * @brief Puts color to given pixel coordinates.
 * 
 * @param imx Pointer to the imx structure.
 * @param pixel	Current pixel.
 * @param color Color code.
 */
void	set_pixel(t_imx *imx, t_coor pixel, int color)
{
	*(unsigned int *)(imx->img->addr + ((int)pixel.y * imx->img->line_length
				+ (int)pixel.x * (imx->img->bits_per_pixel / 8))) = color;
	return ;
}

void	project_scene(t_scene scene, t_imx *window)
{
	t_view	viewbase;
	t_ray	view;
	t_coor	curr_pxl;
	t_inter	first_inter;
	int		color;

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
			color = get_inter_color(scene, first_inter, view);
			set_pixel(window, curr_pxl, color);
			// printf("pixel: x %lf y %lf\n", curr_pxl.x, curr_pxl.y);
			curr_pxl.y++;
		}
		curr_pxl.x++;
	}
	return ;
}
