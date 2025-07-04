/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 15:48:12 by ego               #+#    #+#             */
/*   Updated: 2025/07/04 01:44:05 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_uv	get_plane_uv(t_object *pl, t_hit *h)
{
	t_uv	uv;
	t_coor	up;
	t_coor	local_hit;

	up = (t_coor){0, 1, 0};
	if (fabs(pl->vector.y) > 0.999)
		up = (t_coor){1, 0, 0};
	local_hit = ft_coorsub(h->point, pl->pos);
	h->tangent_u = ft_coornormalize(ft_crossprod(pl->vector, up));
	h->tangent_v = ft_coornormalize(ft_crossprod(pl->vector, h->tangent_u));
	uv.u = ft_dotprod(local_hit, h->tangent_u);
	uv.v = ft_dotprod(local_hit, h->tangent_v);
	uv.u = fmod(uv.u / (2 * TILE_FACTOR), 1);
	uv.v = fmod(uv.v / (2 * TILE_FACTOR), 1);
	if (uv.u < 0)
		uv.u++;
	if (uv.v < 0)
		uv.v++;
	return (uv);
}

static t_uv	get_sphere_uv(t_object *sp, t_hit *hit)
{
	t_uv	uv;
	t_coor	local_hit;
	t_coor	normal;
	t_coor	up;

	normal = ft_coornormalize(ft_coorsub(hit->point, sp->pos));
	up = (t_coor){0, 1, 0};
	if (fabs(normal.y) > 0.999)
		up = (t_coor){1, 0, 0};
	hit->tangent_u = ft_coornormalize(ft_crossprod(normal, up));
	hit->tangent_v = ft_coornormalize(ft_crossprod(normal, hit->tangent_u));
	local_hit = ft_coornormalize(ft_coorsub(hit->point, sp->pos));
	uv.u = 0.5 + (atan2(local_hit.z, local_hit.x) / (2 * M_PI));
	uv.v = 0.5 - (asin(local_hit.y) / M_PI);
	uv.u = fmod(uv.u * TILE_FACTOR, 1.0);
	uv.v = fmod(uv.v * TILE_FACTOR, 1.0);
	return (uv);
}

static t_uv	get_cylinder_uv(t_object *cyl, t_hit *hit)
{
	double	height_proj;

	height_proj = ft_dotprod(cyl->vector, ft_coorsub(hit->point, cyl->pos));
	if (fabs(height_proj - cyl->args[1] / 2.0) < FLT_EPSILON)
		return (get_cylinder_cap_uv(cyl, hit, false));
	if (fabs(height_proj + cyl->args[1] / 2.0) < FLT_EPSILON)
		return (get_cylinder_cap_uv(cyl, hit, true));
	return (get_cylinder_side_uv(cyl, hit));
}

static t_uv	get_cone_uv(t_object *co, t_hit *hit)
{
	double	height_proj;

	height_proj = ft_dotprod(co->vector, ft_coorsub(hit->point, co->pos));
	if (fabs(height_proj - co->args[1]) < FLT_EPSILON)
		return (get_cone_cap_uv(co, hit));
	return (get_cone_side_uv(co, hit));
}

t_uv	get_uv(t_object *obj, t_hit *hit)
{
	if (obj->id == PLANE)
		return (get_plane_uv(obj, hit));
	if (obj->id == SPHERE)
		return (get_sphere_uv(obj, hit));
	if (obj->id == CYLINDER)
		return (get_cylinder_uv(obj, hit));
	else
		return (get_cone_uv(obj, hit));
}
