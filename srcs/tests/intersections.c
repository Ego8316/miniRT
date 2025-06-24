/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:25:06 by ego               #+#    #+#             */
/*   Updated: 2025/06/24 14:52:29 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <assert.h>

void	test_intersections(void)
{
	test_plane_hit();
	test_plane_parallel();
	test_sphere_hit_two_points();
	test_sphere_miss();
	test_sphere_inside_hit();
	test_cylinder_parallel_miss();
	test_cylinder_side_hits();
	test_cylinder_top_cap_hit();
	test_cylinder_inside_out();
	test_ray_misses_cone();
	test_ray_hits_cone_side();
	test_ray_hits_cone_base_cap();
	test_ray_starts_inside_cone();
	test_ray_parallel_inside_radius();
	printf("✅ All tests passed\n");
}
