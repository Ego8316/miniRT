/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:22:37 by ego               #+#    #+#             */
/*   Updated: 2025/07/04 02:02:47 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Computes the normal of a cylinder at the hit point.
 *
 * Handles side surface as well as the two caps.
 *
 * @param cyl Cylinder object.
 * @param hit Point of intersection in world space.
 *
 * @return Unit normal vector.
 */
static t_coor	get_cylinder_normal(t_object *cyl, t_coor hit)
{
	t_coor	center_to_hit;
	double	height_proj;

	center_to_hit = ft_coorsub(hit, cyl->pos);
	height_proj = ft_dotprod(cyl->vector, center_to_hit);
	if (fabs(height_proj - cyl->args[1] / 2.0) < FLT_EPSILON)
		return (cyl->vector);
	if (fabs(height_proj + cyl->args[1] / 2.0) < FLT_EPSILON)
		return (ft_coormult(cyl->vector, -1));
	return (ft_coornormalize(ft_coorsub(center_to_hit,
				ft_coormult(cyl->vector, height_proj))));
}

/**
 * @brief Computes the normal of a cone at the hit point.
 *
 * Treats the base as a cap and otherwise returns the side normal.
 *
 * @param cone Cone object.
 * @param hit Point of intersection in world space.
 *
 * @return Unit normal vector.
 */
static t_coor	get_cone_normal(t_object *cone, t_coor hit)
{
	t_coor	apex_to_hit;
	double	height_proj;
	double	k;

	apex_to_hit = ft_coorsub(hit, cone->pos);
	height_proj = fabs(ft_dotprod(cone->vector, apex_to_hit));
	if (fabs(height_proj + cone->args[1]) < FLT_EPSILON)
		return (cone->vector);
	k = cone->args[0] / (2 * cone->args[1]);
	return (ft_coornormalize(ft_coorsub(apex_to_hit,
				ft_coormult(cone->vector, height_proj * (1 + k * k)))));
}

/**
 * @brief Computes the local surface normal vector for the given intersection
 * and hit point.
 *
 * @param hit Hit information including intersection data and point.
 *
 * @return Normal vector.
 */
t_coor	get_normal(t_hit hit)
{
	t_coor	normal;

	if (hit.inter.obj->id == PLANE)
		normal = hit.inter.obj->vector;
	else if (hit.inter.obj->id == SPHERE)
		normal = ft_coornormalize(ft_coorsub(hit.point, hit.inter.obj->pos));
	else if (hit.inter.obj->id == CYLINDER)
		normal = get_cylinder_normal(hit.inter.obj, hit.point);
	else
		normal = get_cone_normal(hit.inter.obj, hit.point);
	if (hit.inter.obj->color.textured && hit.inter.obj->bump_strength > 0)
		return (get_bump_normal(normal, hit));
	return (ft_coornormalize(normal));
}
