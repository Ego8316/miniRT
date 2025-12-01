/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:17:10 by ego               #+#    #+#             */
/*   Updated: 2025/07/04 02:03:45 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Computes diffuse and specular contributions from a single light.
 *
 * Uses Lambertian diffuse shading and a simple Phong specular term when the
 * object's `specular` value is above 10.
 *
 * @param hit Hit information (point, normal, ray, color).
 * @param light Light being evaluated.
 *
 * @return RGB contribution from the light.
 */
t_coor	get_diffuse_and_specular(t_hit hit, t_light light)
{
	t_coor	hit_to_light;
	t_coor	reflect;
	t_coor	result;
	double	dot;

	hit_to_light = ft_coornormalize(ft_coorsub(light.pos, hit.point));
	dot = ft_dotprod(hit.normal, hit_to_light);
	if (dot <= FLT_EPSILON)
		return ((t_coor){0, 0, 0});
	result = ft_coormult(ft_tensorprod(hit.color, light.color),
			light.brightness * dot);
	reflect = ft_coorsub(hit_to_light, ft_coormult(hit.normal, 2.0 * dot));
	dot = ft_dotprod(reflect, hit.ray);
	if (hit.inter.obj->specular > 10 && dot > 0)
	{
		result = ft_cooradd(result, ft_coormult(light.color,
					light.brightness * pow(dot, hit.inter.obj->specular)));
	}
	return (result);
}

/**
 * @brief Computes the final color for the first intersection on a ray.
 *
 * Adds ambient lighting and per-light diffuse/specular components, skipping
 * lights that are occluded.
 *
 * @param scene Scene data including lights and ambient light.
 * @param inter Intersection data for the closest hit.
 * @param view View ray.
 *
 * @return Packed RGB color for the hit.
 */
int	get_inter_color(t_scene scene, t_inter inter, t_ray view)
{
	t_hit		h;
	t_coor		inter_color;
	t_light		*l;

	if (inter.count == 0)
		return (color_to_rgb((t_coor){0.0, 0.0, 0.0}));
	h.inter = inter;
	h.point = ft_cooradd(view.orig, ft_coormult(view.dir, inter.t[0]));
	h.ray = view.dir;
	h.color = get_object_color(inter.obj, &h);
	h.normal = get_normal(h);
	inter_color = ft_coormult(ft_tensorprod(scene.ambient.color, h.color),
			scene.ambient.ratio);
	l = scene.lights;
	while (l)
	{
		if (!is_shadowed(scene, l->pos, inter, view))
			inter_color = ft_cooradd(inter_color,
					get_diffuse_and_specular(h, *l));
		l = l->next;
	}
	return (color_to_rgb(inter_color));
}
