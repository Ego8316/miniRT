/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersec.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 12:04:27 by ego               #+#    #+#             */
/*   Updated: 2025/06/24 17:02:30 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <assert.h>

void	test_cylinder_parallel_miss(void)
{
	t_object	cyl;
	t_ray		ray;
	t_inter		inter;

	cyl.pos = (t_coor){0, 0, 0};
	cyl.vector = (t_coor){0, 1, 0};
	cyl.args[0] = 2.0;
	cyl.args[1] = 4.0;
	ray.orig = (t_coor){2.0, 0, 0};
	ray.dir = (t_coor){0, 1, 0};
	inter = cylinder_intersec(cyl, ray);
	assert(inter.count == 0);
	printf("✅ test_cylinder_parallel_miss passed!\n");
}

void	test_cylinder_side_hits(void)
{
	t_object	cyl;
	t_ray		ray;
	t_inter		inter;

	cyl.pos = (t_coor){0, 0, 0};
	cyl.vector = (t_coor){0, 1, 0};
	cyl.args[0] = 2.0;
	cyl.args[1] = 4.0;
	ray.orig = (t_coor){2.0, 0, 0};
	ray.dir = (t_coor){-1, 0, 0};
	inter = cylinder_intersec(cyl, ray);
	assert(inter.count == 2);
	assert(inter.inters[0] > 0);
	assert(inter.inters[1] > inter.inters[0]);
	printf("✅ test_cylinder_side_hits passed!\n");
}

void	test_cylinder_top_cap_hit(void)
{
	t_object	cyl;
	t_ray		ray;
	t_inter		inter;

	cyl.pos = (t_coor){0, 0, 0};
	cyl.vector = (t_coor){0, 1, 0};
	cyl.args[0] = 2.0;
	cyl.args[1] = 4.0;
	ray.orig = (t_coor){0, 3, 0};
	ray.dir = (t_coor){0, -1, 0};
	inter = cylinder_intersec(cyl, ray);
	assert(inter.count >= 1);
	assert(inter.inters[0] > 0);
	printf("✅ test_top_cap_hits passed!\n");
}

void	test_cylinder_inside_out(void)
{
	t_object	cyl;
	t_ray		ray;
	t_inter		inter;

	cyl.pos = (t_coor){0, 0, 0};
	cyl.vector = (t_coor){0, 1, 0};
	cyl.args[0] = 2.0;
	cyl.args[1] = 4.0;
	ray.orig = (t_coor){0, 0, 0};
	ray.dir = (t_coor){1, 0, 0};
	inter = cylinder_intersec(cyl, ray);
	assert(inter.count >= 1);
	printf("✅ test_cylinder_inside_out passed!\n");
}
