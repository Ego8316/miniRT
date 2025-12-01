/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:50:29 by vviterbo          #+#    #+#             */
/*   Updated: 2025/07/04 11:42:29 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_inter	get_first_inter(t_scene scene, t_ray view);
bool	is_first(t_inter curr_inter, t_inter first_inter);
void	reorder_inter(t_inter *inter);

/**
 * @brief Finds the closest intersection along a view ray.
 *
 * Iterates through all scene objects, collecting their intersections and
 * keeping the nearest non-negative hit.
 *
 * @param scene Scene containing objects.
 * @param view View ray from the camera through the pixel.
 *
 * @return Intersection data for the closest hit, or `count` zero if none.
 */
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

/**
 * @brief Checks if the current intersection is closer than the previous best.
 *
 * @param curr_inter New intersection candidate.
 * @param first_inter Current closest intersection.
 *
 * @return `true` when `curr_inter` should replace `first_inter`.
 */
bool	is_first(t_inter curr_inter, t_inter first_inter)
{
	if (first_inter.count == 0 || first_inter.t[0] < 0)
		return (curr_inter.count > 0 && curr_inter.t[0] >= 0);
	return (curr_inter.count > 0 && curr_inter.t[0] >= 0
		&& curr_inter.t[0] < first_inter.t[0]);
}

/**
 * @brief Ensures the intersection distances are ordered by proximity.
 *
 * Swaps `t[0]` and `t[1]` so that `t[0]` is the closest non-negative hit when
 * two intersections exist.
 *
 * @param inter Intersection data to reorder.
 */
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
