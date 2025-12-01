/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:03:08 by vviterbo          #+#    #+#             */
/*   Updated: 2025/12/01 01:20:36 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	free_win(t_imx *imx);
int	clean_exit(t_imx *imx);

/**
 * @brief Frees MLX resources, image buffers, and scene data.
 *
 * @param imx Window/image structure.
 *
 * @return 1 after cleanup.
 */
int	free_win(t_imx *imx)
{
	if (!imx)
		return (0);
	free_scene(imx->scene);
	if (imx->img)
	{
		if (imx->img->img)
			mlx_destroy_image(imx->mlx, imx->img->img);
		free(imx->img);
	}
	if (imx->win)
		mlx_destroy_window(imx->mlx, imx->win);
	if (imx->mlx)
	{
		if (LINUX)
		{
			mlx_loop_end(imx->mlx);
			mlx_destroy_display(imx->mlx);
		}
		free(imx->mlx);
	}
	return (1);
}

/**
 * @brief Cleans up resources and exits the program.
 *
 * @param imx Window/image structure.
 *
 * @return Always returns 0.
 */
int	clean_exit(t_imx *imx)
{
	free_win(imx);
	exit(0);
	return (0);
}
