/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:08:10 by vviterbo          #+#    #+#             */
/*   Updated: 2025/06/18 10:52:46 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_intersec	*sphere_intersec(t_object obj, t_ray ray);

t_intersec	*sphere_intersec(t_object obj, t_ray ray)
{
	t_intersec	*x;
	t_coor		sphere_to_ray;
	double		abc[3];
	double		discr;

	x = ft_calloc(1, sizeof(t_intersec));
	if (!x)
		return (NULL);
	sphere_to_ray = ft_coorsubstr(obj.pos, ray.orig);
	abc[0] = ft_dotprod(ray.dir, ray.dir);
	abc[1] = ft_dotprod(ray.dir, sphere_to_ray);
	abc[2] = ft_dotprod(sphere_to_ray, sphere_to_ray);
	discr = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (discr < 0)
		return (x);
	x->inters = ft_calloc(2, sizeof(double));
	if (!x->inters)
		return (free(x), NULL);
	x->inters[0] = (-abc[1] - sqrt(discr)) / (2 * abc[0]);
	x->inters[1] = (-abc[1] + sqrt(discr)) / (2 * abc[0]);
	x->count = 2;
	return (x);
}
