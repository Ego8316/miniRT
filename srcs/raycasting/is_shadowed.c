/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_shadowed.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:06:53 by vviterbo          #+#    #+#             */
/*   Updated: 2025/06/26 00:35:40 by vviterbo         ###   ########.fr       */
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
	int			i;

	obj2light.orig = ft_cooradd(ft_coormult(view.dir, objinter.t[0]), view.orig);
	obj2light.dir = ft_coorsub(light_source, obj2light.orig);
	obj_i = scene.objects;
	while (obj_i)
	{
		if (obj_i == objinter.obj)
		{
			obj_i = obj_i->next;
			continue ;
		}
		light_inter = get_inter(obj_i, obj2light);
		i = -1;
		while (++i < (int)light_inter.count)
		{
			printf("i = %i\n", i);
			if (light_inter.t[i] > DBL_EPSILON)
				return (true);
		}
		obj_i = obj_i->next;
	}
	return (false);
}
