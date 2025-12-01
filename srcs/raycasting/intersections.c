/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 10:51:09 by vviterbo          #+#    #+#             */
/*   Updated: 2025/06/26 00:27:53 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_inter	get_inter(t_object *obj, t_ray ray);

/**
 * @brief Dispatches the intersection routine based on the object type.
 *
 * @param obj Object being tested.
 * @param ray Ray being cast.
 *
 * @return Intersection data for the ray against the given object.
 */
t_inter	get_inter(t_object *obj, t_ray ray)
{
	if (obj->id == SPHERE)
		return (sphere_intersec(obj, ray));
	else if (obj->id == CYLINDER)
		return (cylinder_intersec(obj, ray));
	else if (obj->id == PLANE)
		return (plane_intersec(obj, ray));
	else
		return (cone_intersec(obj, ray));
}
