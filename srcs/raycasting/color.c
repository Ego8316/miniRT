/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:48:38 by ego               #+#    #+#             */
/*   Updated: 2025/07/04 11:44:27 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Clamps a value to the inclusive `[min, max]` range.
 *
 * @param val Value to clamp.
 * @param min Minimum allowed value.
 * @param max Maximum allowed value.
 *
 * @return Clamped value.
 */
double	ft_clamp(double val, double min, double max)
{
	if (val < min)
		return (min);
	if (val > max)
		return (max);
	return (val);
}

/**
 * @brief Converts a color stored as normalized coordinates into an RGB int.
 *
 * Each component in `color` is expected in the 0.0 to 1.0 range and is scaled
 * to the 0-255 range.
 *
 * @param color Color components.
 *
 * @return Packed RGB integer.
 */
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
 * @brief Samples the object's texture at the hit UV coordinates.
 *
 * Clamps the computed texture coordinates to the texture dimensions to avoid
 * overflow, then returns the texel color.
 *
 * @param obj Object with a texture.
 * @param hit Hit data containing the world-space point.
 *
 * @return Sampled color.
 */
static t_coor	get_texture_color(t_object *obj, t_hit *hit)
{
	int		texture_x;
	int		texture_y;

	hit->uv = get_uv(obj, hit);
	texture_x = (int)(hit->uv.u * (TEXTURE_WIDTH - 1));
	if (texture_x < 0)
		texture_x = 0;
	if (texture_x > TEXTURE_WIDTH - 1)
		texture_x = TEXTURE_WIDTH - 1;
	texture_y = (int)((1.0 - hit->uv.v) * (TEXTURE_HEIGHT - 1));
	if (texture_y < 0)
		texture_y = 0;
	if (texture_y > TEXTURE_HEIGHT - 1)
		texture_y = TEXTURE_HEIGHT - 1;
	return (obj->color.texture[texture_y][texture_x]);
}

/**
 * @brief Gets the actual object color. If it is not checkerboard, returns the
 * defined color or texture. Otherwise computes whether it should be black or
 * white depending on the hit point.
 *
 * @param obj Object.
 * @param hit Hit point.
 *
 * @return Actual object color tuple.
 */
t_coor	get_object_color(t_object *obj, t_hit *hit)
{
	bool	x;
	bool	y;
	bool	z;

	if (obj->color.textured)
		return (get_texture_color(obj, hit));
	if (!obj->color.checkerboard)
		return (obj->color.coor);
	x = (int)floor((hit->point.x + DBL_EPSILON) / CHECKER_SIZE) % 2;
	x = (x || (int)floor((hit->point.x - DBL_EPSILON) / CHECKER_SIZE) % 2);
	y = (int)floor((hit->point.y + DBL_EPSILON) / CHECKER_SIZE) % 2;
	y = (y || (int)floor((hit->point.y - DBL_EPSILON) / CHECKER_SIZE) % 2);
	z = (int)floor((hit->point.z + DBL_EPSILON) / CHECKER_SIZE) % 2;
	z = (z || (int)floor((hit->point.z - DBL_EPSILON) / CHECKER_SIZE) % 2);
	if ((x ^ y ^ z) == 0)
		return ((t_coor){1.0, 1.0, 1.0});
	else
		return ((t_coor){0.0, 0.0, 0.0});
}
