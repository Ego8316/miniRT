/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:17:10 by ego               #+#    #+#             */
/*   Updated: 2025/06/25 20:19:13 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// t_coor	get_specular(t_coor hit, t_inter inter, t_light light, t_ray view)
// {
	
// }

int	get_inter_color(t_scene scene, t_inter inter, t_ray view)
{
	t_coor	hit;
	t_coor	obj_color;
	t_coor	inter_color;
	t_light	*light;

	if (inter.count == 0)
		return (color_to_rgb((t_coor){0.0, 0.0, 0.0}));
	hit = ft_cooradd(view.orig, ft_coormult(view.dir, inter.t[0]));
	obj_color = get_object_color(inter.obj->color, hit);
	inter_color = ft_coormult(ft_tensorprod(scene.ambient.color, obj_color),
			scene.ambient.ratio);
	light = scene.lights;
	while (light)
	{
		if (is_shadowed(scene, light->pos, inter, view))
		{
			light = light->next;
			continue ;
		}
		t_coor diffuse = get_diffuse(hit, inter, *light, obj_color);
		printf("diffuse: %lf %lf %lf\n", diffuse.x, diffuse.y, diffuse.z);
		inter_color = ft_cooradd(inter_color, diffuse);
		// inter_color = ft_cooradd(inter_color, get_specular());
		light = light->next;
	}
	// inter_color = ft_coormult(inter_color, 1.0 / 10.0);
	return (color_to_rgb(inter_color));
}
