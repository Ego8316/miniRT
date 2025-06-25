/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 10:51:09 by vviterbo          #+#    #+#             */
/*   Updated: 2025/06/25 20:43:40 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_inter	get_inter(t_object obj, t_ray ray);

t_inter	get_inter(t_object obj, t_ray ray)
{
	if (obj.id == SPHERE)
		return (sphere_intersec(obj, ray));
	else if (obj.id == CYLINDER)
		return (cylinder_intersec(obj, ray));
	else if (obj.id == PLANE)
		return (plane_intersec(obj, ray));
	else
		return (cone_intersec(obj, ray));
}
