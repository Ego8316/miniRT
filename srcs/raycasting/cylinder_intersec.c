/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersec.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 10:52:26 by vviterbo          #+#    #+#             */
/*   Updated: 2025/06/20 12:14:29 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_inter			*cylinder_intersec(t_object obj, t_ray ray);
static t_inter	*local_intersec(t_ray ray);

t_inter	*cylinder_intersec(t_object obj, t_ray ray)
{
	t_ray		normal_ray;
	t_inter	*x;

	(void)obj;
	normal_ray.orig = ray.orig;
	normal_ray.dir = ft_coornormalize(ray.dir);
	x = local_intersec(normal_ray);
	if (!x)
		return (NULL);
	return (x);
}

static t_inter	*local_intersec(t_ray ray)
{
	t_inter	*x;
	double		abc[3];
	double		discr;

	x = ft_calloc(1, sizeof(t_inter));
	if (!x)
		return (NULL);
	abc[0] = ray.dir.x * ray.dir.x + ray.dir.z * ray.dir.z;
	if (abc[0] < DBL_EPSILON)
		return (x);
	abc[1] = 2 * ray.orig.x * ray.dir.x + 2 * ray.orig.z * ray.dir.z;
	abc[2] = ray.orig.x * ray.orig.x + ray.orig.z * ray.orig.z - 1;
	discr = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (discr < 0)
		return (x);
	x->inters = ft_calloc(2, sizeof(double));
	if (!x->inters)
		return (free(x), NULL);
	x->inters[0] = (-abc[1] - sqrt(discr)) / (2 * abc[0]);
	x->inters[1] = (-abc[1] + sqrt(discr)) / (2 * abc[0]);
	if (x->inters[0] > x->inters[1])
		ft_swap_dble(&(x->inters[0]), &(x->inters[1]));
	x->count = 2;
	return (x);
}
