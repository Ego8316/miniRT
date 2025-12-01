/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_uv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 19:23:33 by ego               #+#    #+#             */
/*   Updated: 2025/07/04 02:07:54 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Computes UV coordinates for a cone's cap.
 *
 * Builds tangent axes on the cap and projects the hit point to them.
 *
 * @param cone Cone object.
 * @param h Hit information.
 *
 * @return UV coordinates in [0, 1).
 */
t_uv	get_cone_cap_uv(t_object *cone, t_hit *h)
{
	t_uv	uv;
	t_coor	center;
	t_coor	up;
	t_coor	local_hit;

	center = ft_cooradd(cone->pos, ft_coormult(cone->vector, cone->args[1]));
	if (fabs(cone->vector.x) < 0.9)
		up = (t_coor){1, 0, 0};
	else
		up = (t_coor){0, 1, 0};
	local_hit = ft_coorsub(h->point, center);
	h->tangent_u = ft_coornormalize(ft_crossprod(cone->vector, up));
	h->tangent_v = ft_coornormalize(ft_crossprod(cone->vector, h->tangent_u));
	uv.u = 0.5 + ft_dotprod(local_hit, h->tangent_u) / (cone->args[0]);
	uv.v = 0.5 + ft_dotprod(local_hit, h->tangent_v) / (cone->args[0]);
	return (uv);
}

/**
 * @brief Computes UV coordinates for the side of a cone.
 *
 * @param cone Cone object.
 * @param h Hit information.
 *
 * @return UV coordinates in [0, 1).
 */
t_uv	get_cone_side_uv(t_object *cone, t_hit *h)
{
	t_uv	uv;
	t_coor	up;
	t_coor	radial;
	t_coor	local_hit;

	local_hit = ft_coorsub(h->point, cone->pos);
	uv.v = ft_dotprod(local_hit, cone->vector) / cone->args[1];
	up = (t_coor){0, 1, 0};
	if (fabs(cone->vector.y) > 0.999)
		up = (t_coor){1, 0, 0};
	h->tangent_u = ft_coornormalize(ft_crossprod(cone->vector, up));
	h->tangent_v = ft_coornormalize(ft_crossprod(cone->vector, h->tangent_u));
	radial = ft_coornormalize(ft_coorsub(local_hit, ft_coormult(cone->vector,
					ft_dotprod(local_hit, cone->vector))));
	uv.u = 0.5 + (atan2(ft_dotprod(radial, h->tangent_v),
				ft_dotprod(radial, h->tangent_u)) / (2 * M_PI));
	uv.u = fmod(uv.u * TILE_FACTOR, 1.0);
	uv.v = fmod(uv.v * TILE_FACTOR, 1.0);
	return (uv);
}
