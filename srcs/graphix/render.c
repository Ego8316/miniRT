/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:50:29 by vviterbo          #+#    #+#             */
/*   Updated: 2025/06/24 16:10:58 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_inter	*get_first_inter(t_scene scene, t_ray view);

t_inter	*get_first_inter(t_scene scene, t_ray view)
{
	t_object	*curr_obj;
	t_inter		*curr_inter;
	t_inter		*first_inter;

	curr_obj = scene.objects;
	first_inter = NULL;
	while (curr_obj)
	{
		curr_inter = get_inter(*curr_obj, view);
		first_inter = compare_inters(curr_inter, first_inter);
		curr_obj = curr_obj->next;
	}
	return (first_inter);
}

t_inter	*compare_inter(t_inter *new, t_inter *old)
{
	if (!new)
		return (old);
	else if (!old)
		return (new);
	if (new->count == 2)
	{
		
	}
		
		
}