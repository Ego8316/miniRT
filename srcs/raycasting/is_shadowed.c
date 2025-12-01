/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_shadowed.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:06:53 by vviterbo          #+#    #+#             */
/*   Updated: 2025/07/04 13:16:04 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool		is_shadowed(t_scene scene, t_coor light_source, t_inter objinter, \
	t_ray view);
static bool	check_shadow(t_object *obj_i, t_inter objinter, t_ray obj2light, \
	double dist_to_light);

/**
 * @brief Checks whether a point is shadowed from a light source.
 *
 * Casts a ray from the hit point toward the light and tests it against all
 * objects in the scene.
 *
 * @param scene Current scene data.
 * @param light_source Light position.
 * @param objinter Intersection information for the visible hit.
 * @param view View ray.
 *
 * @return `true` if another object occludes the light, `false` otherwise.
 */
bool	is_shadowed(t_scene scene, t_coor light_source, t_inter objinter, \
	t_ray view)
{
	t_ray		obj2light;
	t_object	*obj_i;
	double		dist_to_light;

	obj2light.orig = ft_cooradd(ft_coormult(view.dir, objinter.t[0]),
			view.orig);
	obj2light.dir = ft_coorsub(light_source, obj2light.orig);
	dist_to_light = sqrt(ft_dotprod(obj2light.dir, obj2light.dir));
	obj2light.dir = ft_coornormalize(obj2light.dir);
	obj_i = scene.objects;
	while (obj_i)
	{
		if (check_shadow(obj_i, objinter, obj2light, dist_to_light))
			return (true);
		obj_i = obj_i->next;
	}
	return (false);
}

/**
 * @brief Tests a single object for blocking the light ray.
 *
 * @param obj_i Candidate occluder.
 * @param objinter Intersection info of the visible object.
 * @param obj2light Ray from the hit point to the light source.
 * @param dist_to_light Distance from the hit point to the light source.
 *
 * @return `true` if the object casts a shadow on the hit point.
 */
static bool	check_shadow(t_object *obj_i, t_inter objinter, t_ray obj2light,
	double dist_to_light)
{
	t_inter		light_inter;
	int			i;

	if (obj_i == objinter.obj)
		return (false);
	light_inter = get_inter(obj_i, obj2light);
	i = -1;
	while (++i < (int)light_inter.count)
	{
		if (light_inter.t[i] > DBL_EPSILON && light_inter.t[i] < dist_to_light)
			return (true);
	}
	return (false);
}
