/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:17:10 by ego               #+#    #+#             */
/*   Updated: 2025/06/25 23:49:08 by ego              ###   ########.fr       */
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
 * @param h Hit point coordinates.
 * @param inter Intersection structure.
 * @param l Current light whose diffuse component is being computed.
 * @param r View ray vector.
 */
t_coor	get_diffuse_and_specular(t_hit hit, t_light light)
{
	t_coor	hit_to_light;
	t_coor	reflect;
	t_coor	result;
	double	dot;

	hit_to_light = ft_coornormalize(ft_coorsub(light.pos, hit.point));
	dot = ft_dotprod(hit.normal, hit_to_light);
	if (dot <= 0)
		dot = 0;
	result = ft_coormult(ft_tensorprod(hit.color, light.color),
			light.brightness * dot);
	reflect = ft_coorsub(ft_coormult(hit.normal, 2.0 * dot), hit_to_light);
	dot = ft_dotprod(reflect, hit.ray);
	if (hit.inter.obj->specular > 0 && dot > 0)
		result = ft_cooradd(result, ft_coormult(light.color,
			0 * light.brightness * pow(dot, hit.inter.obj->specular)));
	return (result);
}

int	get_inter_color(t_scene scene, t_inter inter, t_ray view)
{
	t_hit		h;
	t_coor		inter_color;
	t_light		*l;

	if (inter.count == 0)
		return (color_to_rgb((t_coor){0.0, 0.0, 0.0}));
	h.point = ft_cooradd(view.orig, ft_coormult(view.dir, inter.t[0]));
	h.color = (t_coor){1, 0, 0};
	h.normal = get_normal(inter, h.point);
	h.inter = inter;
	h.ray = view.dir;
	inter_color = ft_coormult(ft_tensorprod(scene.ambient.color,
			inter.obj->color.coor), scene.ambient.ratio);
	l = scene.lights;
	while (l)
	{
		// if (!is_shadowed(scene, light->pos, inter, view))
		inter_color = ft_cooradd(inter_color, get_diffuse_and_specular(h, *l));
		l = l->next;
	}
	return (color_to_rgb(inter_color));
}
