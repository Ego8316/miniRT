/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 15:04:12 by ego               #+#    #+#             */
/*   Updated: 2025/07/04 02:17:24 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
