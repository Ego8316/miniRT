/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:08:10 by vviterbo          #+#    #+#             */
/*   Updated: 2025/06/20 15:04:31 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_inter	*sphere_intersec(t_object obj, t_ray ray);

t_inter	*sphere_intersec(t_object obj, t_ray ray)
{
	t_inter	*inter;
	t_coor	sphere_to_ray;
	double	abc[3];
	double	discr;

	inter = ft_calloc(1, sizeof(t_inter));
	if (!inter)
		return (NULL);
	sphere_to_ray = ft_coorsub(obj.pos, ray.orig);
	abc[0] = ft_dotprod(ray.dir, ray.dir);
	abc[1] = ft_dotprod(ray.dir, sphere_to_ray);
	abc[2] = ft_dotprod(sphere_to_ray, sphere_to_ray);
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
