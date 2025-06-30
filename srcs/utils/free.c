/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 19:42:54 by ego               #+#    #+#             */
/*   Updated: 2025/06/27 22:17:02 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Frees a string if it is not NULL and sets it to NULL.
 * 
 * @param s Pointer to the string to free.
 * 
 * @return Always returns `false` for convenience.
 */
bool	*free_str(char **s)
{
	if (s && *s)
	{
		free(*s);
		*s = NULL;
	}
	return (false);
}

/**
 * @brief Frees the lights linked list.
 * 
 * @param lights Lights list to be freed.
 */
void	free_lights(t_light *lights)
{
	if (!lights)
		return ;
	free_lights(lights->next);
	free(lights);
}

/**
 * @brief Frees the objects linked list.
 * 
 * @param objects Objects list to be freed.
 */
void	free_objects(t_object *objects)
{
	if (!objects)
		return ;
	free_objects(objects->next);
	free(objects);
}

/**
 * @brief Frees all allocated resources in the scene structure.
 * 
 * @param s Pointer to the scene structure.
 * 
 * @return Always returns 1 for convenience.
 */
int	free_scene(t_scene *s)
{
	if (s->fd > 0)
		close(s->fd);
	free_lights(s->lights);
	free_objects(s->objects);
	return (1);
}
