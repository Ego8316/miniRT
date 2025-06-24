/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:50:29 by vviterbo          #+#    #+#             */
/*   Updated: 2025/06/24 17:30:10 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_inter	get_first_inter(t_scene scene, t_ray view);
t_inter	*compare_inter(t_inter new, t_inter *old);
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
		first_inter = compare_inters(curr_inter, first_inter);
		curr_obj = curr_obj->next;
	}
	if (!first_inter)
	{
		ft_bzero(&curr_inter, sizeof(t_inter));
		return (curr_inter);
	}
	return (*first_inter);
}

t_inter	*compare_inter(t_inter new, t_inter *old)
{
	if (!old || !old->count || old->t[0] < 0)
		return (&new);
	reorder_inter(&new);
	if (!new.count || new.t[0] < 0)
		return (old);
	if (new.t[0] < old->t[0])
		return (&new)
	else
		return (old);
}

void	reorder_inter(t_inter *inter)
{
	if (inter->count < 2)
		return ;
	if (inter->t[0] * inter->t[1] < 0 && inter->t[0] < 0)
		ft_swap_dble(&(inter->t[0]), &(inter->t[1]));
	else if (inter->t[0] > 0 && inter->t[0] > inter->t[1])
		ft_swap_dble(&(inter->t[0]), &(inter->t[1]));
	return ;
}