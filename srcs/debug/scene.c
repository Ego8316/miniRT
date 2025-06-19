/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:49:29 by ego               #+#    #+#             */
/*   Updated: 2025/06/16 17:18:55 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Prints details of camera.
 * 
 * @param c Camera to print.
 */
void	print_camera(t_camera *c)
{
	printf("Camera:\n\tPos:\t(%.3lf, %.3lf, %.3lf)\n",
		c->vector.orig.x, c->vector.orig.y, c->vector.orig.z);
	printf("\tVector:\t(%.3lf, %.3lf, %.3lf)\n",
		c->vector.dir.x, c->vector.dir.y, c->vector.dir.z);
	printf("\tFOV:\t%.0lf\n", c->fov);
	return ;
}

/**
 * @brief Prints a summary of the entire scene.
 * 
 * Includes file info, ambient light, camera, lights and objects.
 * 
 * @param s Scene structure.
 */
void	print_scene(t_scene *s)
{
	printf("\n-------------------  SCENE  INFORMATION  -------------------\n");
	printf("File:\n\tfilename:\t\t%s\n\tfile descriptor:\t%i\n",
		s->filename, s->fd);
	if (s->ambient.ratio)
		print_ambient(&s->ambient);
	print_camera(&s->camera);
	print_lights(&s->lights);
	print_objects(&s->objects);
	printf("------------------------------------------------------------\n");
	return ;
}
