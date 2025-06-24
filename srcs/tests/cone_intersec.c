/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_intersec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 14:42:22 by ego               #+#    #+#             */
/*   Updated: 2025/06/24 15:32:36 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <assert.h>

void	test_ray_misses_cone(void)
{
	t_object	cone;
	t_ray		ray;
	t_inter		*inter;
	
	cone.pos = (t_coor){0, 0, 0};
	cone.vector = (t_coor){0, 1, 0};
	cone.args[0] = 2.0;
	cone.args[1] = 4.0;
	ray.orig = (t_coor){5, 5, 5};
	ray.dir = (t_coor){1, 0, 0};
	inter = cone_intersec(cone, ray);
	assert(inter != NULL);
	assert(inter->count == 0);
	free(inter->inters);
	free(inter);
	printf("✅ test_ray_misses_cone passed\n");
}

void	test_ray_hits_cone_side(void)
{
	t_object	cone;
	t_ray		ray;
	t_inter		*inter;

	cone.pos = (t_coor){0, 0, 0};
	cone.vector = (t_coor){0, 1, 0};
	cone.args[0] = 2.0;
	cone.args[1] = 4.0;

	ray.orig = (t_coor){2, 2, 0};
	ray.dir = (t_coor){-1, 0, 0};
	inter = cone_intersec(cone, ray);
	assert(inter != NULL);
	assert(inter->count >= 1);
	free(inter->inters);
	free(inter);
	printf("✅ test_ray_hits_cone_side passed\n");
}

void	test_ray_hits_cone_base_cap(void)
{
	t_object	cone;
	t_ray		ray;
	t_inter		*inter;

	cone.pos = (t_coor){0, 0, 0};
	cone.vector = (t_coor){0, 1, 0};
	cone.args[0] = 2.0;
	cone.args[1] = 4.0;

	ray.orig = (t_coor){0, 5, 0};
	ray.dir = (t_coor){0, -1, 0};
	inter = cone_intersec(cone, ray);
	assert(inter != NULL);
	assert(inter->count >= 1);
	free(inter->inters);
	free(inter);
	printf("✅ test_ray_hits_cone_base_cap passed\n");
}

void	test_ray_starts_inside_cone(void)
{
	t_object	cone;
	t_ray		ray;
	t_inter		*inter;

	cone.pos = (t_coor){0, 0, 0};
	cone.vector = (t_coor){0, 1, 0};
	cone.args[0] = 2.0;
	cone.args[1] = 4.0;

	ray.orig = (t_coor){0, 1, 0};
	ray.dir = (t_coor){0, 1, 0};
	inter = cone_intersec(cone, ray);
	assert(inter != NULL);
	assert(inter->count >= 1);
	free(inter->inters);
	free(inter);
	printf("✅ test_ray_starts_inside_cone passed\n");
}

void	test_ray_parallel_inside_radius(void)
{
	t_object	cone;
	t_ray		ray;
	t_inter		*inter;

	cone.pos = (t_coor){0, 0, 0};
	cone.vector = (t_coor){0, 1, 0};
	cone.args[0] = 2.0;
	cone.args[1] = 4.0;

	ray.orig = (t_coor){0.5, -1, 0};
	ray.dir = (t_coor){0, 1, 0};
	inter = cone_intersec(cone, ray);
	assert(inter != NULL);
	assert(inter->count >= 1);
	free(inter->inters);
	free(inter);
	printf("✅ test_ray_parallel_inside_radius passed\n");
}
