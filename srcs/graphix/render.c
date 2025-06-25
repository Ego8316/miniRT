/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:50:29 by vviterbo          #+#    #+#             */
/*   Updated: 2025/06/25 20:43:14 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_inter	get_first_inter(t_scene scene, t_ray view);
t_inter	*compare_inter(t_inter *new, t_inter *old);
void	reorder_inter(t_inter *inter);

t_inter	get_first_inter(t_scene scene, t_ray view)
{
	t_object	*curr_obj;
	t_inter		curr_inter;
	t_inter		*first_inter;

	curr_obj = scene.objects;
	first_inter = NULL;
	while (curr_obj)
	{
		curr_inter = get_inter(*curr_obj, view);
		curr_inter.obj = curr_obj;
		//printf("t0 = %f, t1 = %f\n", curr_inter.t[0], curr_inter.t[1]);
		first_inter = compare_inter(&curr_inter, first_inter);
		//printf("t0 = %f, t1 = %f\n", curr_inter.t[0], curr_inter.t[1]);
		curr_obj = curr_obj->next;
	}
	if (!first_inter)
	{
		ft_bzero(&curr_inter, sizeof(t_inter));
		return (curr_inter);
	}
	return (*first_inter);
}

t_inter	*compare_inter(t_inter *new, t_inter *old)
{
	if (!old || !old->count || old->t[0] < 0)
		return (new);
	reorder_inter(new);
	if (!new->count || new->t[0] < 0)
		return (old);
	if (new->t[0] < old->t[0])
		return (new);
	else
		return (old);
}

void	reorder_inter(t_inter *inter)
{
	double	tmp;

	if (inter->count < 2)
		return ;
	if ((inter->t[0] * inter->t[1] < 0 && inter->t[0] < 0)
		|| (inter->t[0] > 0 && inter->t[0] > inter->t[1]))
	{
		tmp = inter->t[0];
		inter->t[0] = inter->t[1];
		inter->t[1] = tmp;
	}
	return ;
}
