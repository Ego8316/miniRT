/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_shadowed.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:06:53 by vviterbo          #+#    #+#             */
/*   Updated: 2025/06/25 18:34:52 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	is_shadowed(t_scene scene, t_coor light_source, t_inter objinter, \
	t_ray view);

bool	is_shadowed(t_scene scene, t_coor light_source, t_inter objinter, \
	t_ray view)
{
	t_inter		light_inter;
	t_ray		obj2light;
	t_object	*obj_i;
	size_t		i;

	obj2light.orig = ft_cooradd(ft_coormult(view.dir, objinter.t[0]), view.orig);
	obj2light.dir = ft_coorsub(light_source, obj2light.orig);
	obj_i = scene.objects;
	while (obj_i)
	{
		if (obj_i != objinter.obj)
		{
			light_inter = get_inter(*obj_i, obj2light);
			i = -1;
			while (++i < light_inter.count)
			{
				if (light_inter.t[i] > 0)
					return (true);
			}
		}
		obj_i = obj_i->next;
	}
	return (false);
}
