/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_intersec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:08:10 by vviterbo          #+#    #+#             */
/*   Updated: 2025/06/20 18:09:50 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_inter	*plane_intersec(t_object obj, t_ray ray);

t_inter	*plane_intersec(t_object obj, t_ray ray)
{
	t_inter	*x;
	double	denom;

	x = (t_inter *)ft_calloc(1, sizeof(t_inter));
	if (!x)
		return (NULL);
	denom = ft_dotprod(ray.dir, obj.vector);
	if (fabs(denom) < DBL_EPSILON)
		return (x);
	x->inters = ft_calloc(1, sizeof(double));
	if (!x->inters)
		return (free(x), NULL);
	*x->inters = ft_dotprod(ft_coorsub(obj.pos, ray.orig), obj.vector) / denom;
	x->count++;
	return (x);
}
