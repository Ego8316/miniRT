/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 12:05:17 by ego               #+#    #+#             */
/*   Updated: 2025/06/24 12:09:21 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <assert.h>

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

void	test_sphere_miss(void)
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
