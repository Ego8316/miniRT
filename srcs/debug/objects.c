/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 03:55:35 by ego               #+#    #+#             */
/*   Updated: 2025/06/19 01:33:34 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Prints details of a single object.
 * 
 * @param o Object to print.
 * @param i Index of the object.
 */
void	print_object(t_object *o, int i)
{
	printf("\n\tObject %i:\n\t\tType:\t\t%s\n",
		i + 1, get_id_string(o->id));
	printf("\t\tPos:\t\t(%.3lf, %.3lf, %.3lf)\n",
		o->pos.x, o->pos.y, o->pos.z);
	printf("\t\tVector:\t\t(%.3lf, %.3lf, %.3lf)\n",
		o->vector.x, o->vector.y, o->vector.z);
	printf("\t\tArgs:\t\t(%.3lf, %.3lf, %.3lf)\n",
		o->args.x, o->args.y, o->args.z);
	printf("\t\tReflectivity:\t%.3lf (%p)\n",
		o->reflectivity, &o->reflectivity);
	printf("\t\tColor:\t\t");
	if (o->color.checkerboard)
		printf("checkerboard\n");
	else
		printf("(%.3lf, %.3lf, %.3lf)\n",
			o->color.coor.x, o->color.coor.y, o->color.coor.z);
	printf("\t\tBump strength:\t%.3lf (%p)\n",
		o->bump_strength, &o->bump_strength);
	return ;
}

/**
 * @brief Prints all objects in the linked list.
 * 
 * @param objects Objects linked list.
 */
void	print_objects(t_object **objects)
{
	t_object	*o;
	int			i;

	printf("Objects:");
	if (!objects || !*objects)
	{
		printf("\tNONE\n");
		return ;
	}
	o = *objects;
	i = 0;
	while (o)
	{
		print_object(o, i);
		++i;
		o = o->next;
	}
	return ;
}
