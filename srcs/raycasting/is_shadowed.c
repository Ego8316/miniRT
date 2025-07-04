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
