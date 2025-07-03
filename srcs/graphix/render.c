/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:50:29 by vviterbo          #+#    #+#             */
/*   Updated: 2025/07/01 18:00:35 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_inter	get_first_inter(t_scene scene, t_ray view);
bool	is_first(t_inter curr_inter, t_inter first_inter);
void	reorder_inter(t_inter *inter);

t_inter	get_first_inter(t_scene scene, t_ray view)
{
	t_object	*curr_obj;
	t_inter		curr_inter;
	t_inter		first_inter;

	curr_obj = scene.objects;
	ft_bzero(&first_inter, sizeof(t_inter));
	while (curr_obj)
	{
		curr_inter = get_inter(curr_obj, view);
		reorder_inter(&curr_inter);
		if (is_first(curr_inter, first_inter))
			first_inter = curr_inter;
		curr_obj = curr_obj->next;
	}
	return (first_inter);
}

bool	is_first(t_inter curr_inter, t_inter first_inter)
{
	if (first_inter.count == 0 || first_inter.t[0] < 0)
		return (curr_inter.count > 0 && curr_inter.t[0] >= 0);
	return (curr_inter.count > 0 && curr_inter.t[0] >= 0
			&& curr_inter.t[0] < first_inter.t[0]);
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
