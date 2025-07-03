/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_uv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 19:23:33 by ego               #+#    #+#             */
/*   Updated: 2025/07/03 22:37:38 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_uv	get_cone_cap_uv(t_object *cone, t_coor hit)
{
	t_uv	uv;
	t_coor	center;
	t_coor	tangent_u;
	t_coor	tangent_v;
	t_coor	up;

	center = ft_cooradd(cone->pos, ft_coormult(cone->vector, cone->args[1]));
	if (fabs(cone->vector.x) < 0.9)
		up = (t_coor){1, 0, 0};
	else
		up = (t_coor){0, 1, 0};
	hit = ft_coorsub(hit, center);
	tangent_u = ft_coornormalize(ft_crossprod(cone->vector, up));
	tangent_v = ft_coornormalize(ft_crossprod(cone->vector, tangent_u));
	uv.u = 0.5 + ft_dotprod(hit, tangent_u) / (cone->args[0]);
	uv.v = 0.5 + ft_dotprod(hit, tangent_v) / (cone->args[0]);
	return (uv);
}

t_uv	get_cone_side_uv(t_object *cone, t_coor hit)
{
	t_uv	uv;
	t_coor	up;
	t_coor	radial;
	t_coor	tangent_u;
	t_coor	tangent_v;

	hit = ft_coorsub(hit, cone->pos);
	uv.v = ft_dotprod(hit, cone->vector) / cone->args[1];
	up = (t_coor){0, 1, 0};
	if (fabs(cone->vector.y) > 0.999)
		up = (t_coor){1, 0, 0};
	tangent_u = ft_coornormalize(ft_crossprod(cone->vector, up));
	tangent_v = ft_coornormalize(ft_crossprod(cone->vector, tangent_u));
	radial = ft_coornormalize(ft_coorsub(hit, ft_coormult(cone->vector,
					ft_dotprod(hit, cone->vector))));
	uv.u = 0.5 + (atan2(ft_dotprod(radial, tangent_v),
				ft_dotprod(radial, tangent_u)) / (2 * M_PI));
	uv.u = fmod(uv.u * TILE_FACTOR, 1.0);
	uv.v = fmod(uv.v * TILE_FACTOR, 1.0);
	return (uv);
}
