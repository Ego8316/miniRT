/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:22:37 by ego               #+#    #+#             */
/*   Updated: 2025/06/26 00:33:29 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_coor	get_cylinder_normal(t_object *cyl, t_coor hit)
{
	t_coor	center_to_hit;
	double	height_proj;

	center_to_hit = ft_coorsub(hit, cyl->pos);
	height_proj = ft_dotprod(cyl->vector, center_to_hit);
	if (height_proj + cyl->args[1] / 2 <= DBL_EPSILON)
		return (ft_coormult(cyl->vector, -1));
	if (height_proj - cyl->args[1] / 2 <= DBL_EPSILON)
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
	height_proj = ft_dotprod(cone->vector, apex_to_hit);
	if (height_proj <= DBL_EPSILON)
		return (ft_coormult(cone->vector, -1));
	if (height_proj - cone->args[1] <= DBL_EPSILON)
		return (cone->vector);
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
	if (inter.obj->id == PLANE)
		return (inter.obj->vector);
	else if (inter.obj->id == SPHERE)
		return (ft_coornormalize(ft_coorsub(hit, inter.obj->pos)));
	else if (inter.obj->id == CYLINDER)
		return (get_cylinder_normal(inter.obj, hit));
	else
		return (get_cone_normal(inter.obj, hit));
}
