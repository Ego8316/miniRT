/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_intersec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:08:10 by vviterbo          #+#    #+#             */
/*   Updated: 2025/06/20 13:00:45 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_inter		*cube_intersec(t_object obj, t_ray ray);
static void	set_local_intersec(double *minmax, double orig, double dir);

t_inter	*cube_intersec(t_object obj, t_ray ray)
{
	t_inter	*x;
	double	minmax[2];
	double	minmax_x[2];
	double	minmax_y[2];
	double	minmax_z[2];

	(void)obj;
	set_local_intersec(minmax_x, ray.orig.x, ray.dir.x);
	set_local_intersec(minmax_y, ray.orig.y, ray.dir.y);
	set_local_intersec(minmax_z, ray.orig.z, ray.dir.z);
	minmax[0] = ft_max(ft_max(minmax_x[0], minmax_y[0]), minmax_z[0]);
	minmax[1] = ft_min(ft_max(minmax_x[1], minmax_y[1]), minmax_z[1]);
	x = ft_calloc(1, sizeof(t_inter));
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
		return ;
	tmp = minmax[0];
	minmax[0] = minmax[1];
	minmax[1] = tmp;
}
