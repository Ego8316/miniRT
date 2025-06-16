/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 03:56:05 by ego               #+#    #+#             */
/*   Updated: 2025/06/16 03:58:02 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Prints details of the ambient light.
 * 
 * @param a Ambient to print.
 */
void	print_ambient(t_ambient *a)
{
	printf("Ambient:\n\tRatio:\t%.3lf\n\tColor:\t(%.3lf, %.3lf, %.3lf)\n",
		a->ratio, a->color.x, a->color.y, a->color.z);
	return ;
}

/**
 * @brief Prints details of a single light.
 * 
 * @param l Light to print.
 * @param i Index of the light.
 */
void	print_light(t_light *l, int i)
{
	printf("\n\tLight %i:\n", i + 1);
	printf("\t\tPos:\t\t(%.3lf, %.3lf, %.3lf)\n",
		l->pos.x, l->pos.y, l->pos.z);
	printf("\t\tBrightness:\t%.3lf\n", l->brightness);
	printf("\t\tColor:\t\t(%.3lf, %.3lf, %.3lf)\n",
		l->color.x, l->color.y, l->color.z);
	return ;
}

/**
 * @brief Prints all lights in the linked list.
 * 
 * @param lights Lights linked list.
 */
void	print_lights(t_light **lights)
{
	t_light	*l;
	int		i;

	printf("Lights:");
	if (!lights || !*lights)
	{
		printf("\t\tNONE\n");
		return ;
	}
	l = *lights;
	i = 0;
	while (l)
	{
		print_light(l, i);
		++i;
		l = l->next;
	}
	return ;
}
