/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:25:06 by ego               #+#    #+#             */
/*   Updated: 2025/06/24 12:07:26 by ego              ###   ########.fr       */
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
	printf("✅ All tests passed\n");
}
