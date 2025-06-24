/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:08:10 by vviterbo          #+#    #+#             */
/*   Updated: 2025/06/21 14:16:48 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_inter	*sphere_intersec(t_object obj, t_ray ray);

t_inter	*sphere_intersec(t_object obj, t_ray ray)
{
	t_inter	*inter;
	t_coor	ray_to_sphere;
	double	abc[3];
	double	discr;
	double	radius;

	inter = ft_calloc(1, sizeof(t_inter));
	if (!inter)
		return (NULL);
	radius = obj.args[0] / 2;
	ray_to_sphere = ft_coorsub(ray.orig, obj.pos);
	abc[0] = ft_dotprod(ray.dir, ray.dir);
	abc[1] = 2 * ft_dotprod(ray.dir, ray_to_sphere);
	abc[2] = ft_dotprod(ray_to_sphere, ray_to_sphere) - radius * radius;
	discr = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (discr < 0)
		return (inter);
	inter->inters = ft_calloc(2, sizeof(double));
	if (!inter->inters)
		return (free(inter), NULL);
	inter->inters[0] = (-abc[1] - sqrt(discr)) / (2 * abc[0]);
	inter->inters[1] = (-abc[1] + sqrt(discr)) / (2 * abc[0]);
	inter->count = 2;
	return (inter);
}
