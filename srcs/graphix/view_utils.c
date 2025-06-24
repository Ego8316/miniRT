/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 14:11:07 by vviterbo          #+#    #+#             */
/*   Updated: 2025/06/24 15:40:56 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_coor	get_viewdir(t_view viewbase, t_coor curr_pxl, t_coor size);
t_view	ft_init_view(t_scene scene, t_coor screensize);

t_coor	get_viewdir(t_view viewbase, t_coor curr_pxl, t_coor size)
{
	t_coor	rel_coor;
	t_coor	view_ray;

	rel_coor.x = (2 * curr_pxl.x / (viewbase.size.x - 1) - 1)
		* viewbase.h_width;
	rel_coor.y = (2 * curr_pxl.y / (viewbase.size.y - 1) - 1)
		* viewbase.h_height;
	view_ray = ft_cooradd(ft_coormult(viewbase.R, rel_coor.x),
		ft_coormult(viewbase.U, rel_coor.y));
	view_ray = ft_cooradd(viewbase.F, view_ray);
	return (view_ray);
}

t_view	ft_init_view(t_scene scene, t_coor screensize)
{
	t_view	viewbase;

	viewbase.F = scene.camera.vector.dir;
	viewbase.R = ft_crossprod(viewbase.F, ft_initcoor(0, 1, 0));
	if (ft_norm(viewbase.R) > 0.01)
		viewbase.R = ft_coornormalize(viewbase.R);
	else
		viewbase.R = ft_coornormalize(ft_crossprod(viewbase.F,
			ft_initcoor(0, 0, 1)));
	viewbase.U = ft_coornormalize(ft_crossprod(viewbase.F, viewbase.R));
	viewbase.orig = scene.camera.vector.orig;
	viewbase.size = screensize;
	viewbase.h_width = tan(scene.camera.fov / 2); 
	viewbase.h_height = (viewbase.size.y / viewbase.size.x) * viewbase.h_width;
	return (viewbase);
}
