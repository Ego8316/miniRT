/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:03:08 by vviterbo          #+#    #+#             */
/*   Updated: 2025/06/25 14:56:34 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	free_win(t_imx *imx);

int	free_win(t_imx *imx)
{
	if (imx)
	{
		if (imx->img)
			mlx_destroy_image(imx->mlx, imx->img);
		if (imx->win)
			mlx_destroy_window(imx->mlx, imx->win);
		mlx_loop_end(imx->mlx);
		mlx_destroy_display(imx->mlx);
		free(imx);
	}
	return (0);
}
