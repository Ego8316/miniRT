/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 14:11:07 by vviterbo          #+#    #+#             */
/*   Updated: 2025/07/04 11:41:47 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_coor	get_viewdir(t_view viewbase, t_coor curr_pxl);
t_view	ft_init_view(t_scene scene, t_coor screensize);

/**
 * @brief Computes the normalized viewing direction for a pixel.
 *
 * Maps the pixel coordinates to camera space using the view basis vectors.
 *
 * @param viewbase Precomputed view basis and screen data.
 * @param curr_pxl Current pixel coordinates.
 *
 * @return Normalized direction vector for the ray through the pixel.
 */
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
	view_ray = ft_cooradd(viewbase.f, view_ray);
	view_ray = ft_coornormalize(view_ray);
	return (view_ray);
}

/**
 * @brief Initializes the view basis vectors from the scene camera.
 *
 * Builds forward, right and up vectors, camera origin, and precomputes half
 * widths/heights for perspective projection.
 *
 * @param scene Scene containing the camera.
 * @param screensize Screen resolution.
 *
 * @return View basis data.
 */
t_view	ft_init_view(t_scene scene, t_coor screensize)
{
	t_view	viewbase;
	double	angle;

	viewbase.f = scene.camera.vector.dir;
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
