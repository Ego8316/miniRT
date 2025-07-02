/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:03:08 by vviterbo          #+#    #+#             */
/*   Updated: 2025/07/01 08:47:27 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	free_win(t_imx *imx);
int	clean_exit(t_imx *imx);

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
		//mlx_loop_end(imx->mlx)
		free(imx->mlx);
	}
	return (1);
}

int	clean_exit(t_imx *imx)
{
	free_win(imx);
	exit(0);
	return (0);
}
