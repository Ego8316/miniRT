/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:22:37 by ego               #+#    #+#             */
/*   Updated: 2025/06/30 13:27:25 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_coor	get_cylinder_normal(t_object *cyl, t_coor hit)
{
	t_coor	center_to_hit;
	double	height_proj;

	center_to_hit = ft_coorsub(hit, cyl->pos);
	height_proj = ft_dotprod(cyl->vector, center_to_hit);
	if (height_proj < DBL_EPSILON - cyl->args[1] / 2.0)
		return (ft_coormult(cyl->vector, -1));
	if (height_proj > cyl->args[1] / 2.0 - DBL_EPSILON)
		return (cyl->vector);
	return (ft_coornormalize(ft_coorsub(center_to_hit,
				ft_coormult(cyl->vector, height_proj))));
}

static t_coor	get_cone_normal(t_object *cone, t_coor hit)
{
	t_coor	apex_to_hit;
	double	height_proj;
	double	k;

	apex_to_hit = ft_coorsub(hit, cone->pos);
	height_proj = fabs(ft_dotprod(cone->vector, apex_to_hit));
	// printf("height_proj: %f | height: %f\n", height_proj, cone->args[1]);
	if (height_proj < DBL_EPSILON - cone->args[1])
		return (cone->vector);
	// printf("ici\n");
	k = cone->args[0] / (2 * cone->args[1]);
	return (ft_coornormalize(ft_coorsub(apex_to_hit,
				ft_coormult(cone->vector, height_proj * (1 + k * k)))));
}

/**
 * @brief Computes the local surface normal vector for the given intersection
 * and hit point.
 * 
 * @param inter Current intersection (containing the object).
 * @param hit Hit point coordinates.
 * 
 * @return Normal vector.
 */
t_coor	get_normal(t_inter inter, t_coor hit)
{
	t_coor	bump;
	t_coor	normal;

	if (inter.obj->id == PLANE)
		normal = inter.obj->vector;
	else if (inter.obj->id == SPHERE)
		normal = ft_coornormalize(ft_coorsub(hit, inter.obj->pos));
	else if (inter.obj->id == CYLINDER)
		normal = get_cylinder_normal(inter.obj, hit);
	else
		normal = get_cone_normal(inter.obj, hit);
	bump.x = sin(10 * hit.x) * inter.obj->bump_strength;
	bump.y = cos(10 * hit.y) * inter.obj->bump_strength;
	bump.z = sin(10 * hit.z) * inter.obj->bump_strength;
	return (ft_coornormalize(ft_cooradd(normal, bump)));
}
