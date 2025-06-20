/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_intersec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:08:10 by vviterbo          #+#    #+#             */
/*   Updated: 2025/06/20 15:41:02 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_inter	*plane_intersec(t_object obj, t_ray ray);

t_inter	*plane_intersec(t_object obj, t_ray ray)
{
	t_inter	*x;
	double	prod;

	x = (t_inter *)ft_calloc(1, sizeof(t_inter));
	if (!x)
		return (NULL);
	prod = ft_dotprod(ray.dir, obj.vector);
	if (fabs(prod) < DBL_EPSILON)
		return (x);
	x->inters = ft_calloc(1, sizeof(double));
	if (!x->inters)
		return (free(x), NULL);
	*x->inters = ft_dotprod(ft_coorsub(obj.pos, ray.orig), obj.vector) / prod;
	x->count++;
	return (x);
}
