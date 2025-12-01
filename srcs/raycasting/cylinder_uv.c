/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_uv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 19:22:57 by ego               #+#    #+#             */
/*   Updated: 2025/07/04 01:39:14 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Computes UV coordinates for a cylinder cap.
 *
 * Builds tangent axes on the cap plane and projects the hit point to them.
 *
 * @param cyl Cylinder object.
 * @param h Hit information.
 * @param top `true` when the hit is on the top cap, `false` for the bottom.
 *
 * @return UV coordinates in [0, 1).
 */
t_uv	get_cylinder_cap_uv(t_object *cyl, t_hit *h, bool top)
{
	t_uv	uv;
	t_coor	center;
	t_coor	up;
	t_coor	local_hit;

	center = ft_coorsub(cyl->pos, ft_coormult(cyl->vector, cyl->args[1] / 2));
	if (top)
		center = ft_cooradd(center, ft_coormult(cyl->vector, cyl->args[1]));
	if (fabs(cyl->vector.x) < 0.9)
		up = (t_coor){1, 0, 0};
	else
		up = (t_coor){0, 1, 0};
	local_hit = ft_coorsub(h->point, center);
	h->tangent_u = ft_coornormalize(ft_crossprod(cyl->vector, up));
	h->tangent_v = ft_coornormalize(ft_crossprod(cyl->vector, h->tangent_u));
	uv.u = 0.5 + ft_dotprod(local_hit, h->tangent_u) / (cyl->args[0]);
	uv.v = 0.5 + ft_dotprod(local_hit, h->tangent_v) / (cyl->args[0]);
	return (uv);
}

/**
 * @brief Computes UV coordinates for the side of a cylinder.
 *
 * @param cyl Cylinder object.
 * @param h Hit information.
 *
 * @return UV coordinates in [0, 1).
 */
t_uv	get_cylinder_side_uv(t_object *cyl, t_hit *h)
{
	t_uv	uv;
	t_coor	up;
	t_coor	radial;
	t_coor	local_hit;

	local_hit = ft_coorsub(h->point, cyl->pos);
	uv.v = 0.5 + ft_dotprod(local_hit, cyl->vector) / cyl->args[1];
	up = (t_coor){0, 1, 0};
	if (fabs(cyl->vector.y) > 0.999)
		up = (t_coor){1, 0, 0};
	h->tangent_u = ft_coornormalize(ft_crossprod(cyl->vector, up));
	h->tangent_v = ft_coornormalize(ft_crossprod(cyl->vector, h->tangent_u));
	radial = ft_coornormalize(ft_coorsub(local_hit, ft_coormult(cyl->vector,
					ft_dotprod(local_hit, cyl->vector))));
	uv.u = 0.5 + (atan2(ft_dotprod(radial, h->tangent_v),
				ft_dotprod(radial, h->tangent_u)) / (2 * M_PI));
	uv.u = fmod(uv.u * TILE_FACTOR, 1.0);
	uv.v = fmod(uv.v * TILE_FACTOR, 1.0);
	return (uv);
}
