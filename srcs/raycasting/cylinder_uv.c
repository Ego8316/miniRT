/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_uv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 19:22:57 by ego               #+#    #+#             */
/*   Updated: 2025/07/03 21:37:02 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_uv	get_cylinder_cap_uv(t_object *cyl, t_coor hit, bool top)
{
	t_uv	uv;
	t_coor	center;
	t_coor	tangent_u;
	t_coor	tangent_v;
	t_coor	up;

	center = ft_coorsub(cyl->pos, ft_coormult(cyl->vector, cyl->args[1] / 2));
	if (top)
		center = ft_cooradd(center, ft_coormult(cyl->vector, cyl->args[1]));
	if (fabs(cyl->vector.x) < 0.9)
		up = (t_coor){1, 0, 0};
	else
		up = (t_coor){0, 1, 0};
	hit = ft_coorsub(hit, center);
	tangent_u = ft_coornormalize(ft_crossprod(cyl->vector, up));
	tangent_v = ft_coornormalize(ft_crossprod(cyl->vector, tangent_u));
	uv.u = 0.5 + ft_dotprod(hit, tangent_u) / (cyl->args[0]);
	uv.v = 0.5 + ft_dotprod(hit, tangent_v) / (cyl->args[0]);
	return (uv);
}

t_uv	get_cylinder_side_uv(t_object *cyl, t_coor hit)
{
	t_uv	uv;
	t_coor	up;
	t_coor	radial;
	t_coor	tangent_u;
	t_coor	tangent_v;

	hit = ft_coorsub(hit, cyl->pos);
	uv.v = 0.5 + ft_dotprod(hit, cyl->vector) / cyl->args[1];
	up = (t_coor){0, 1, 0};
	if (fabs(cyl->vector.y) > 0.999)
		up = (t_coor){1, 0, 0};
	tangent_u = ft_coornormalize(ft_crossprod(cyl->vector, up));
	tangent_v = ft_coornormalize(ft_crossprod(cyl->vector, tangent_u));
	radial = ft_coornormalize(ft_coorsub(hit, ft_coormult(cyl->vector,
					ft_dotprod(hit, cyl->vector))));
	uv.u = 0.5 + (atan2(ft_dotprod(radial, tangent_v),
				ft_dotprod(radial, tangent_u)) / (2 * M_PI));
	uv.u = fmod(uv.u * TILE_FACTOR, 1.0);
	uv.v = fmod(uv.v * TILE_FACTOR, 1.0);
	return (uv);
}
