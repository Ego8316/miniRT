/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 15:48:12 by ego               #+#    #+#             */
/*   Updated: 2025/07/03 22:56:08 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_uv	get_plane_uv(t_object *pl, t_coor hit)
{
	t_uv	uv;
	t_coor	up;
	t_coor	tangent_u;
	t_coor	tangent_v;

	up = (t_coor){0, 1, 0};
	if (fabs(pl->vector.y) > 0.999)
		up = (t_coor){1, 0, 0};
	tangent_u = ft_coornormalize(ft_crossprod(pl->vector, up));
	tangent_v = ft_coornormalize(ft_crossprod(pl->vector, tangent_u));
	hit = ft_coorsub(hit, pl->pos);
	uv.u = ft_dotprod(hit, tangent_u);
	uv.v = ft_dotprod(hit, tangent_v);
	uv.u = fmod(uv.u / (2 * TILE_FACTOR), 1);
	uv.v = fmod(uv.v / (2 * TILE_FACTOR), 1);
	if (uv.u < 0)
		uv.u++;
	if (uv.v < 0)
		uv.v++;
	return (uv);
}

static t_uv	get_sphere_uv(t_object *sp, t_coor hit)
{
	t_uv	uv;

	hit = ft_coornormalize(ft_coorsub(hit, sp->pos));
	uv.u = 0.5 + (atan2(hit.z, hit.x) / (2 * M_PI));
	uv.v = 0.5 - (asin(hit.y) / M_PI);
	uv.u = fmod(uv.u * TILE_FACTOR, 1.0);
	uv.v = fmod(uv.v * TILE_FACTOR, 1.0);
	return (uv);
}

static t_uv	get_cylinder_uv(t_object *cyl, t_coor hit)
{
	double	height_proj;

	height_proj = ft_dotprod(cyl->vector, ft_coorsub(hit, cyl->pos));
	if (fabs(height_proj - cyl->args[1] / 2.0) < FLT_EPSILON)
		return (get_cylinder_cap_uv(cyl, hit, false));
	if (fabs(height_proj + cyl->args[1] / 2.0) < FLT_EPSILON)
		return (get_cylinder_cap_uv(cyl, hit, true));
	return (get_cylinder_side_uv(cyl, hit));
}

static t_uv	get_cone_uv(t_object *co, t_coor hit)
{
	double	height_proj;

	height_proj = ft_dotprod(co->vector, ft_coorsub(hit, co->pos));
	if (fabs(height_proj - co->args[1]) < FLT_EPSILON)
		return (get_cone_cap_uv(co, hit));
	return (get_cone_side_uv(co, hit));
}

t_uv	get_uv(t_object *obj, t_coor hit)
{
	t_uv	uv;

	ft_bzero(&uv, sizeof(t_uv));
	if (obj->id == PLANE)
		uv = get_plane_uv(obj, hit);
	if (obj->id == SPHERE)
		uv = get_sphere_uv(obj, hit);
	if (obj->id == CYLINDER)
		uv = get_cylinder_uv(obj, hit);
	else
		uv = get_cone_uv(obj, hit);
	return (uv);
}
