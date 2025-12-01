/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:08:10 by vviterbo          #+#    #+#             */
/*   Updated: 2025/06/26 00:33:52 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_inter	sphere_intersec(t_object *obj, t_ray ray);

/**
 * @brief Computes the intersection points of a ray with a sphere.
 *
 * Solves the quadratic equation for the ray-sphere intersection using the
 * sphere radius stored in `args[0]`. When the discriminant is negative, the
 * returned intersection has a zero `count`.
 *
 * @param obj Sphere object.
 * @param ray Ray being cast.
 *
 * @return Intersection data with up to two hit distances stored in `t`.
 */
t_inter	sphere_intersec(t_object *obj, t_ray ray)
{
	t_inter	inter;
	t_coor	ray_to_sphere;
	double	abc[3];
	double	discr;
	double	radius;

	radius = obj->args[0] / 2;
	ray_to_sphere = ft_coorsub(ray.orig, obj->pos);
	abc[0] = ft_dotprod(ray.dir, ray.dir);
	abc[1] = 2 * ft_dotprod(ray.dir, ray_to_sphere);
	abc[2] = ft_dotprod(ray_to_sphere, ray_to_sphere) - radius * radius;
	discr = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	ft_bzero(&inter, sizeof(t_inter));
	if (discr < 0)
		return (inter);
	inter.t[0] = (-abc[1] - sqrt(discr)) / (2 * abc[0]);
	inter.t[1] = (-abc[1] + sqrt(discr)) / (2 * abc[0]);
	inter.count = 2;
	inter.obj = obj;
	return (inter);
}
