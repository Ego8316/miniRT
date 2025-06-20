/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:25:06 by ego               #+#    #+#             */
/*   Updated: 2025/06/20 16:13:59 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
# include <assert.h>

void	test_plane_hit(void)
{
	t_ray		ray;
	t_object	plane;
	t_inter		*res;

	ray.orig = ft_initcoor(0, 0, 0);
	ray.dir = ft_initcoor(0, 0, 1);
	plane.pos = ft_initcoor(0, 0, 5);
	plane.vector = ft_initcoor(0, 0, -1);
	normalize_vector(&plane.vector);
	res = plane_intersec(plane, ray);
	assert(res != NULL);
	assert(res->inters != NULL);
	assert(res->count == 1);
	assert(fabs(res->inters[0] - 5.0) < DBL_EPSILON);
	printf("✅ test_plane_hit passed!\n");
	free(res->inters);
	free(res);
}

void	test_plane_parallel(void)
{
	t_ray		ray;
	t_object	plane;
	t_inter		*res;

	ray.orig = ft_initcoor(0, 0, 0);
	ray.dir = ft_initcoor(1, 0, 0);
	plane.pos = ft_initcoor(0, 0, 5);
	plane.vector = ft_initcoor(0, 0, 1);
	res = plane_intersec(plane, ray);
	assert(res != NULL);
	assert(res->count == 0);
	assert(res->inters == NULL);
	printf("✅ test_plane_parallel passed!\n");
	free(res);
}

void	test_sphere_hit_two_points(void)
{
	t_ray		ray;
	t_object	sphere;
	t_inter		*res;

	ray.orig = ft_initcoor(0, 0, -5);
	ray.dir = ft_initcoor(0, 0, 1);
	sphere.pos = ft_initcoor(0, 0, 0);
	sphere.args[0] = 2.0;
	res = sphere_intersec(sphere, ray);
	assert(res != NULL);
	assert(res->inters != NULL);
	assert(res->count == 2);
	assert(fabs(res->inters[0] - 4.0) < DBL_EPSILON);
	assert(fabs(res->inters[1] - 6.0) < DBL_EPSILON);
	printf("✅ test_sphere_hit_two_points passed!\n");
	free(res->inters);
	free(res);
}

void	test_sphere_miss()
{
	t_ray		ray;
	t_object	sphere;
	t_inter		*res;

	ray.orig = ft_initcoor(0, 0, -5);
	ray.dir = ft_initcoor(0, 1, 0);
	sphere.pos = ft_initcoor(0, 0, 0);
	sphere.args[0] = 2.0;
	res = sphere_intersec(sphere, ray);
	assert(res != NULL);
	assert(res->count == 0);
	assert(res->inters == NULL);
	printf("✅ test_sphere_miss passed!\n");
	free(res);
}

void	test_sphere_inside_hit(void)
{
	t_ray		ray;
	t_object	sphere;
	t_inter		*res;

	ray.orig = ft_initcoor(0, 0, 0);
	ray.dir = ft_initcoor(0, 0, 1);
	sphere.pos = ft_initcoor(0, 0, 0); 
	sphere.args[0] = 2.0;
	res = sphere_intersec(sphere, ray);
	assert(res != NULL);
	assert(res->inters != NULL);
	assert(res->count == 2);
	assert(res->inters[0] < 0.0);
	assert(res->inters[1] > 0.0);
	assert(fabs(res->inters[1] - 1.0) < DBL_EPSILON);
	printf("✅ test_sphere_inside_hit passed!\n");
	free(res->inters);
	free(res);
}

void	test_intersections(void)
{
    test_plane_hit();
    test_plane_parallel();
    test_sphere_hit_two_points();
    test_sphere_miss();
    test_sphere_inside_hit();
	printf("✅ All tests passed\n");
}
