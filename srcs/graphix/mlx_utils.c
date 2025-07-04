/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:03:08 by vviterbo          #+#    #+#             */
/*   Updated: 2025/07/04 02:14:57 by ego              ###   ########.fr       */
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
		mlx_loop_end(imx->mlx);
		mlx_destroy_display(imx->mlx);
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
