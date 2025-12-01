/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_intersec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:08:10 by vviterbo          #+#    #+#             */
/*   Updated: 2025/07/03 17:48:45 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_inter	plane_intersec(t_object *obj, t_ray ray);

/**
 * @brief Computes the intersection of a ray with a plane.
 *
 * Solves for the distance along the ray where it meets the plane with normal
 * `obj->vector` passing through `obj->pos`. If the ray is parallel to the
 * plane, no intersections are recorded.
 *
 * @param obj Plane object.
 * @param ray Ray being cast.
 *
 * @return Intersection data; `count` remains zero when the ray is parallel.
 */
t_inter	plane_intersec(t_object *obj, t_ray ray)
{
	t_inter	inter;
	double	denom;

	denom = ft_dotprod(ray.dir, obj->vector);
	ft_bzero(&inter, sizeof(t_inter));
	if (fabs(denom) < DBL_EPSILON)
		return (inter);
	inter.t[0] = ft_dotprod(ft_coorsub(obj->pos, ray.orig),
			obj->vector) / denom;
	inter.count++;
	inter.obj = obj;
	return (inter);
}
