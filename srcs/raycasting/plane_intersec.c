/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_intersec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:08:10 by vviterbo          #+#    #+#             */
/*   Updated: 2025/06/20 18:37:41 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_inter	*plane_intersec(t_object obj, t_ray ray);

t_inter	*plane_intersec(t_object obj, t_ray ray)
{
	t_inter	*inter;
	double	prod;

	inter = (t_inter *)ft_calloc(1, sizeof(t_inter));
	if (!inter)
		return (NULL);
	prod = ft_dotprod(ray.dir, obj.vector);
	if (prod < DBL_EPSILON)
		return (inter);
	inter->inters = ft_calloc(1, sizeof(double));
	if (!inter->inters)
		return (free(inter), NULL);
	*inter->inters = ft_dotprod(ft_coorsub(obj.pos, ray.orig), obj.vector) / prod;
	inter->count++;
	return (inter);
}
