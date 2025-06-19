/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 01:10:37 by ego               #+#    #+#             */
/*   Updated: 2025/06/19 01:10:49 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Adds a new light to the end of a linked list of lights. If the list
 * is empty, the new light becomes the head.
 * 
 * @param new New light to add.
 * @param lights Pointer to the head of the lights list.
 */
void	add_light_to_list(t_light *new, t_light **lights)
{
	t_light	*l;

	if (!*lights)
	{
		*lights = new;
		return ;
	}
	l = *lights;
	while (l->next)
		l = l->next;
	l->next = new;
	return ;
}

/**
 * @brief Adds a new object to the end of a linked list of objects. If the list
 * is empty, the new object becomes the head.
 * 
 * @param new New object to add.
 * @param objects Pointer to the head of the objects list.
 */
void	add_object_to_list(t_object *new, t_object **objects)
{
	t_object	*o;

	if (!*objects)
	{
		*objects = new;
		return ;
	}
	o = *objects;
	while (o->next)
		o = o ->next;
	o->next = new;
	return ;
}
