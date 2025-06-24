/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_intersec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 12:04:53 by ego               #+#    #+#             */
/*   Updated: 2025/06/24 17:02:10 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <assert.h>

void	test_plane_hit(void)
{
	t_ray		ray;
	t_object	plane;
	t_inter		res;

	ray.orig = ft_initcoor(0, 0, 0);
	ray.dir = ft_initcoor(0, 0, 1);
	plane.pos = ft_initcoor(0, 0, 5);
	plane.vector = ft_initcoor(0, 0, -1);
	normalize_vector(&plane.vector);
	res = plane_intersec(plane, ray);
	assert(res.count == 1);
	assert(fabs(res.inters[0] - 5.0) < DBL_EPSILON);
	printf("✅ test_plane_hit passed!\n");
}

void	test_plane_parallel(void)
{
	t_ray		ray;
	t_object	plane;
	t_inter		res;

	ray.orig = ft_initcoor(0, 0, 0);
	ray.dir = ft_initcoor(1, 0, 0);
	plane.pos = ft_initcoor(0, 0, 5);
	plane.vector = ft_initcoor(0, 0, 1);
	res = plane_intersec(plane, ray);
	assert(res.count == 0);
	printf("✅ test_plane_parallel passed!\n");
}
