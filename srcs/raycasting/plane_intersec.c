/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_intersec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:08:10 by vviterbo          #+#    #+#             */
/*   Updated: 2025/06/27 22:38:36 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_inter	plane_intersec(t_object *obj, t_ray ray);

t_inter	plane_intersec(t_object *obj, t_ray ray)
{
	t_inter	inter;
	double	denom;

	denom = ft_dotprod(ray.dir, obj->vector);
	ft_bzero(&inter, sizeof(t_inter));
	if (fabs(denom) < DBL_EPSILON)
		return (inter);
	inter.t[0] = ft_dotprod(ft_coorsub(obj->pos, ray.orig), obj->vector) / denom;
	inter.count++;
	inter.obj = obj;
	return (inter);
}
