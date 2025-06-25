/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:17:10 by ego               #+#    #+#             */
/*   Updated: 2025/06/25 21:42:05 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Computes the diffuse contribution of the given light, using Lambert
 * model:
 * 	diffuse = (light color) x (object color) x light ratio x max(0, cos theta)
 * where theta is the angle between the local surface normal and the light
 * vector.
 * 
 * @param hit Hit point coordinates.
 * @param inter Intersection structure.
 * @param light Current light whose diffuse component is being computed.
 * @param obj_color Object color.
 */
t_coor	get_diffuse(t_coor hit, t_coor normal, t_light light, t_coor obj_color)
{
	t_coor	hit_to_light;
	double	dot;

	hit_to_light = ft_coornormalize(ft_coorsub(light.pos, hit));
	dot = ft_dotprod(normal, hit_to_light);
	if (dot <= 0)
		dot = 0;
	return (ft_coormult(ft_tensorprod(obj_color, light.color),
			light.brightness * dot));
}


// t_coor	get_specular(t_coor hit, t_inter inter, t_light light, t_ray view)
// {
	
// }

int	get_inter_color(t_scene scene, t_inter inter, t_ray view)
{
	const t_coor	hit = ft_cooradd(view.orig, ft_coormult(view.dir, inter.t[0]));
	t_coor	obj_color;
	t_coor	inter_color;
	t_coor	normal;
	t_light	*light;

	if (inter.count == 0)
		return (color_to_rgb((t_coor){0.0, 0.0, 0.0}));
	obj_color  = get_object_color(inter.obj->color, hit);
	inter_color = ft_coormult(ft_tensorprod(scene.ambient.color, obj_color),
			scene.ambient.ratio);
	normal = get_normal(inter, hit);
	light = scene.lights;
	while (light)
	{
		// if (!is_shadowed(scene, light->pos, inter, view))
		// {
		t_coor diffuse = get_diffuse(hit, normal, *light, obj_color);
		// printf("diffuse: %lf %lf %lf\n", diffuse.x, diffuse.y, diffuse.z);
		inter_color = ft_cooradd(inter_color, diffuse);
		// inter_color = ft_cooradd(inter_color, get_specular());
		// }
		light = light->next;
	}
	return (color_to_rgb(inter_color));
}
