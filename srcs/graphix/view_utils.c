/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 14:11:07 by vviterbo          #+#    #+#             */
/*   Updated: 2025/07/01 17:58:51 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_coor	get_viewdir(t_view viewbase, t_coor curr_pxl);
t_view	ft_init_view(t_scene scene, t_coor screensize);

t_coor	get_viewdir(t_view viewbase, t_coor curr_pxl)
{
	t_coor	rel_coor;
	t_coor	view_ray;

	rel_coor.x = (2 * curr_pxl.x / (viewbase.size.x - 1) - 1)
		* viewbase.h_width;
	rel_coor.y = (1 - 2 * curr_pxl.y / (viewbase.size.y - 1))
		* viewbase.h_height;
	view_ray = ft_cooradd(ft_coormult(viewbase.r, rel_coor.x),
			ft_coormult(viewbase.u, rel_coor.y));
	if (curr_pxl.x == 0 && curr_pxl.y == 0)
	{
		printf("%f, %f\n", rel_coor.x, rel_coor.y);
		printf("(%f, %f %f), (%f, %f, %f)\n", viewbase.r.x, viewbase.r.y, viewbase.r.z, viewbase.u.x, viewbase.u.y, viewbase.u.z);
		printf("viewray : %f, %f %f\n", view_ray.x, view_ray.y, view_ray.z);
	}
	view_ray = ft_cooradd(viewbase.f, view_ray);
	view_ray = ft_coornormalize(view_ray);
	if (curr_pxl.x == 0 && curr_pxl.y == 0)
	{
		printf("%f, %f\n", rel_coor.x, rel_coor.y);
		printf("(%f, %f %f), (%f, %f, %f)\n", viewbase.r.x, viewbase.r.y, viewbase.r.z, viewbase.u.x, viewbase.u.y, viewbase.u.z);
		printf("viewray : %f, %f %f\n", view_ray.x, view_ray.y, view_ray.z);
	}
	return (view_ray);
}

t_view	ft_init_view(t_scene scene, t_coor screensize)
{
	t_view	viewbase;
	double	angle;

	viewbase.f = scene.camera.vector.dir;
	printf("viewbase f = %f, %f, %f\n", viewbase.f.x, viewbase.f.y, viewbase.f.z);
	viewbase.r = ft_crossprod(viewbase.f, ft_initcoor(0, 1, 0));
	if (ft_norm(viewbase.r) > 0.01)
		viewbase.r = ft_coornormalize(viewbase.r);
	else
		viewbase.r = ft_coornormalize(ft_crossprod(viewbase.f,
					ft_initcoor(0, 0, 1)));
	viewbase.u = ft_coornormalize(ft_crossprod(viewbase.r, viewbase.f));
	viewbase.orig = scene.camera.vector.orig;
	viewbase.size = screensize;
	angle = M_PI * scene.camera.fov / 180;
	viewbase.h_width = tan(angle / 2);
	viewbase.h_height = (viewbase.size.y / viewbase.size.x) * viewbase.h_width;
	return (viewbase);
}
