/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 15:04:12 by ego               #+#    #+#             */
/*   Updated: 2025/12/01 01:17:26 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Samples the bump map at the given UV coordinates.
 *
 * Coordinates are clamped to the texture size to avoid overflows.
 *
 * @param hit Hit information including the object pointer.
 * @param u U coordinate in [0, 1].
 * @param v V coordinate in [0, 1].
 *
 * @return Height value from the bump map.
 */
static double	sample_bump_map(t_hit hit, double u, double v)
{
	int	bump_x;
	int	bump_y;

	bump_x = (int)(u * (TEXTURE_WIDTH - 1));
	if (bump_x < 0)
		bump_x = 0;
	if (bump_x > TEXTURE_WIDTH - 1)
		bump_x = TEXTURE_WIDTH - 1;
	bump_y = (int)((1.0 - v) * (TEXTURE_HEIGHT - 1));
	if (bump_y < 0)
		bump_y = 0;
	if (bump_y > TEXTURE_HEIGHT - 1)
		bump_y = TEXTURE_HEIGHT - 1;
	return (hit.inter.obj->color.bump[bump_y][bump_x]);
}

/**
 * @brief Perturbs the surface normal using the bump map around the hit point.
 *
 * Computes finite differences in the U and V directions and adjusts the
 * original normal by the bump strength of the object.
 *
 * @param original_normal Unmodified geometric normal.
 * @param hit Hit data containing UVs, tangents and object reference.
 *
 * @return Normal vector adjusted by the bump map.
 */
t_coor	get_bump_normal(t_coor original_normal, t_hit hit)
{
	double			height_center;
	double			height_u;
	double			height_v;
	double			dhdu;
	double			dhdv;

	height_center = sample_bump_map(hit, hit.uv.u, hit.uv.v);
	height_u = sample_bump_map(hit,
			hit.uv.u + 1.0 / (double)TEXTURE_WIDTH, hit.uv.v);
	height_v = sample_bump_map(hit,
			hit.uv.u, hit.uv.v + 1.0 / (double)TEXTURE_HEIGHT);
	dhdu = height_u - height_center;
	dhdv = height_v - height_center;
	return (ft_coornormalize(ft_coorsub(ft_coorsub(original_normal,
					ft_coormult(hit.tangent_u,
						dhdu * 5 * hit.inter.obj->bump_strength)),
				ft_coormult(hit.tangent_v,
					dhdv * 5 * hit.inter.obj->bump_strength))));
}
