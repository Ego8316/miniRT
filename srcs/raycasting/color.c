/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:48:38 by ego               #+#    #+#             */
/*   Updated: 2025/06/30 13:58:46 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static double	ft_clamp(double val, double min, double max)
{
	if (val < min)
		return (min);
	if (val > max)
		return (max);
	return (val);
}

int	color_to_rgb(t_coor color)
{
	int	r;
	int	g;
	int	b;

	r = (int)(255.0 * ft_clamp(color.x, 0.0, 1.0));
	g = (int)(255.0 * ft_clamp(color.y, 0.0, 1.0));
	b = (int)(255.0 * ft_clamp(color.z, 0.0, 1.0));
	return (r << 16 | g << 8 | b);
}

/**
 * @brief Gets the actual object color. If it is not checkerboard, returns the
 * defined color. Otherwise computes whether it should black or white depending
 * on the hit point.
 * 
 * @param color Object color.
 * @param hit Hit point coordinates.
 * 
 * @return Actual object color tuple.
 */
t_coor	get_object_color(t_color color, t_coor hit)
{
	bool	x;
	bool	y;
	bool	z;

	if (!color.checkerboard)
		return (color.coor);
	x = (int)floor((hit.x + DBL_EPSILON) / CHECKER_SIZE) % 2;
	x = x || (int)floor((hit.x - DBL_EPSILON) / CHECKER_SIZE) % 2;
	y = (int)floor((hit.y + DBL_EPSILON) / CHECKER_SIZE) % 2;
	y = y || (int)floor((hit.y - DBL_EPSILON) / CHECKER_SIZE) % 2;
	z = (int)floor((hit.z + DBL_EPSILON) / CHECKER_SIZE) % 2;
	z = z || (int)floor((hit.z - DBL_EPSILON) / CHECKER_SIZE) % 2;
	if ((x ^ y ^ z) == 0)
		return ((t_coor){1.0, 1.0, 1.0});
	else
		return ((t_coor){0.0, 0.0, 0.0});
}
