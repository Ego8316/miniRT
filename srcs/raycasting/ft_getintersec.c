/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getintersec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:08:10 by vviterbo          #+#    #+#             */
/*   Updated: 2025/06/16 14:56:55 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_intersec	*get_intersec(t_object obj, t_ray ray)
{
	if (obj.id == SPHERE)
		return (sphere_intersec(obj, ray));
	else if (obj.id == PLANE)
		return (cube_interesec(obj, ray));
}

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

t_intersec	*cube_intersec(t_object obj, t_ray ray)
{
	t_intersec	*x;
	double		minmax[2];
	double		minmax_x[2];
	double		minmax_y[2];
	double		minmax_z[2];

	set_local_intersec(minmax_x, ray.orig.x, ray.dir.x);
	set_local_intersec(minmax_y, ray.orig.y, ray.dir.y);
	set_local_intersec(minmax_z, ray.orig.z, ray.dir.z);
	minmax[0] = ft_max(ft_max(minmax_x[0], minmax_y[0]), minmax_z[0]);
	minmax[1] = ft_min(ft_max(minmax_x[1], minmax_y[1]), minmax_z[1]);
	x = ft_calloc(1, sizeof(t_intersec));
	if (!x)
		return (NULL);
	if (minmax[0] <= minmax[1])
	{
		x->inters = ft_calloc(2, sizeof(double));
		if (!x->inters)
			return (free(x), NULL);
		x->count = 2;
		x->inters[0] = minmax[0];
		x->inters[1] = minmax[1];
	}
	return (x);
}

void	set_local_intersec(double *minmax, double orig, double dir)
{
	double	tmp;

	if (ft_abs(dir) > DBL_EPSILON)
	{
		minmax[0] = (-1 - orig) / dir;
		minmax[1] = (1 - orig) / dir;
	}
	else
	{
		minmax[0] = (-1 - orig) / (DBL_EPSILON);
		minmax[1] = (1 - orig) / (DBL_EPSILON);
	}
	if (minmax[0] < minmax[1])
		return (minmax);
	tmp = minmax[0];
	minmax[0] = minmax[1];
	minmax[1] = tmp;
}
