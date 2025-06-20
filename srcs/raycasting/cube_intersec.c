/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_intersec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:08:10 by vviterbo          #+#    #+#             */
/*   Updated: 2025/06/20 14:52:37 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_inter		*cube_intersec(t_object obj, t_ray ray);
static void	set_local_intersec(double *minmax, double orig, double dir);

t_inter	*cube_intersec(t_object obj, t_ray ray)
{
	t_inter	*inter;
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
	inter = ft_calloc(1, sizeof(t_inter));
	if (!inter)
		return (NULL);
	if (minmax[0] <= minmax[1])
	{
		inter->inters = ft_calloc(2, sizeof(double));
		if (!inter->inters)
			return (free(inter), NULL);
		inter->count = 2;
		inter->inters[0] = minmax[0];
		inter->inters[1] = minmax[1];
	}
	return (inter);
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
