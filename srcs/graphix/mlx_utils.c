/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victorviterbo <victorviterbo@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:03:08 by vviterbo          #+#    #+#             */
/*   Updated: 2025/09/10 14:57:32 by victorviter      ###   ########.fr       */
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
		#ifdef __linux__
			mlx_loop_end(imx->mlx);
			mlx_destroy_display(imx->mlx);
		#endif
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
