/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersec.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 10:52:26 by vviterbo          #+#    #+#             */
/*   Updated: 2025/06/20 14:37:29 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_inter			*cylinder_intersec(t_object obj, t_ray ray);
static t_inter	*local_intersec(t_ray ray);
void			filter_w_bounds(t_inter *inter, t_object obj, t_ray);

t_inter	*cylinder_intersec(t_object obj, t_ray ray)
{
	t_ray	normal_ray;
	t_inter	*inter;

	(void)obj;
	normal_ray.orig = ray.orig;
	normal_ray.dir = ft_coornormalize(ray.dir);
	inter = local_intersec(normal_ray);
	if (!inter)
		return (NULL);
	filter_w_bounds(inter, obj, normal_ray);
	return (inter);
}

static t_inter	*local_intersec(t_ray ray)
{
	t_inter	*inter;
	double	abc[3];
	double	discr;

	inter = ft_calloc(1, sizeof(t_inter));
	if (!inter)
		return (NULL);
	abc[0] = ray.dir.x * ray.dir.x + ray.dir.z * ray.dir.z;
	if (abc[0] < DBL_EPSILON)
		return (inter);
	abc[1] = 2 * ray.orig.x * ray.dir.x + 2 * ray.orig.z * ray.dir.z;
	abc[2] = ray.orig.x * ray.orig.x + ray.orig.z * ray.orig.z - 1;
	discr = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (discr < 0)
		return (inter);
	inter->inters = ft_calloc(2, sizeof(double));
	if (!inter->inters)
		return (free(inter), NULL);
	inter->inters[0] = (-abc[1] - sqrt(discr)) / (2 * abc[0]);
	inter->inters[1] = (-abc[1] + sqrt(discr)) / (2 * abc[0]);
	if (inter->inters[0] > inter->inters[1])
		ft_swap_dble(&(inter->inters[0]), &(inter->inters[1]));
	inter->count = 2;
	return (inter);
}

void	filter_w_bounds(t_inter *inter, t_object obj, t_ray ray)
{
	double	y;
	size_t	i;
	size_t	n;

	
	n = 0;
	while (n < inter->count)
	{
		y = ray.orig.y + inter->inters[n] * ray.dir.y;
		if (y < - obj.args[HEIGHT] / 2 || y > obj.args[HEIGHT] / 2)
		{
			i = n;
			while (i < inter->count - 1)
			{
				inter->inters[i] = inter->inters[i + 1];
				i++;
			}
			inter->count = inter->count - 1;
		}
		else
			n += 1;
	}
}
