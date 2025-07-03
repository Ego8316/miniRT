/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 15:48:12 by ego               #+#    #+#             */
/*   Updated: 2025/07/03 16:26:27 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_uv	get_plane_uv(t_object *obj, t_coor hit)
{
	t_uv	uv;
	t_coor	up;
	t_coor	tangent_u;
	t_coor	tangent_v;

	up = (t_coor){0, 1, 0};
	if (fabs(obj->vector.y) > 0.999)
		up = (t_coor){1, 0, 0};
	tangent_u = ft_coornormalize(ft_crossprod(obj->vector, up));
	tangent_v = ft_coornormalize(ft_crossprod(obj->vector, tangent_u));
	hit = ft_coornormalize(ft_coorsub(hit, obj->pos));
	uv.u = ft_dotprod(hit, tangent_u);
	uv.v = ft_dotprod(hit, tangent_v);
	uv.u -= floor(uv.u);
	uv.v -= floor(uv.v);
	return (uv);
}

static t_uv	get_sphere_uv(t_object *obj, t_coor hit)
{
	t_uv	uv;

	hit = ft_coornormalize(ft_coorsub(hit, obj->pos));
	uv.u = 0.5 + (atan2(hit.z, hit.x) / (2 * M_PI));
	uv.v = 0.5 - (asin(hit.y) / M_PI);
	return (uv);
}

t_uv	get_uv(t_object *obj, t_coor hit)
{
	t_uv	uv;
	static	double u_min = 1;
	static	double u_max = 0;
	static	double v_min = 1;
	static	double v_max = 0;

	ft_bzero(&uv, sizeof(t_uv));
	if (!obj)
	{
		printf("u range [%lf ; %lf] v range [%lf ; %lf]\n", u_min, u_max, v_min, v_max);
		return (uv);
	}
	if (obj->id == PLANE)
		uv = get_plane_uv(obj, hit);
	if (obj->id == SPHERE)
		uv = get_sphere_uv(obj, hit);
	if (uv.u > u_max)
		u_max = uv.u;
	if (uv.v > v_max)
		v_max = uv.v;
	if (uv.u < u_min)
		u_min = uv.u;
	if (uv.v < v_min)
		v_min = uv.v;
	return (uv);
}
