/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 14:57:42 by ego               #+#    #+#             */
/*   Updated: 2025/06/15 18:55:40 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <math.h>
# include <stdbool.h>
# include "macros.h"
# include "../lib/libft/libft.h"
# include "../lib/mlx/mlx.h"

// Typedefs and enums

typedef enum e_object_type
{
	SP,
	PL,
	CY,
	CO,
	HY,
	PA
}	t_object_type;

// Structures

/**
 * @brief Ambient lighting settings for the scene.
 */
typedef struct s_ambient
{
	double	ratio;	/** Intensity ratio of the ambient light. */
	t_coor	color;	/** Color of the ambient light. */
}	t_ambient;

/**
 * @brief Camera settings for the scene.
 */
typedef struct s_camera
{
	t_vec	vector;	/** Position and direction of the camera. */
	int		fov;	/** Field of view of the camera in degrees. */
}	t_camera;

/**
 * @brief Linked list of point light sources in the scene.
 */
typedef struct s_light
{
	t_coor			pos;		/** Position of the light source. */
	double			brightness;	/** Brightness ratio of the light. */
	t_coor			color;		/** Color of the light. */
	struct s_light	*next;		/** Pointer to the next light. */
}	t_light;

/**
 * @brief Linked list of objects in the scene.
 */
typedef struct s_object
{
	t_object_type	type;			/** Type of the object. */
	t_coor			pos;			/** Position of the object. */
	t_coor			vector;			/**	Orientation vector (if applicable). */
	t_coor			args;			/**	Additional parameters. */
	double			reflectivity;	/**	Reflectivity coefficient. */
	bool			checkerboard;	/** Flag to enable checkerboard texture. */
	t_coor			color;			/**	Color of the object. */
	bool			bump;			/** Flag to enable bump mapping. */
	double			bump_strength;	/** Strength of the bump mapping effect. */
	struct s_object	*next;			/**	Pointer to the next object. */
}	t_object;

/**
 * @brief The main scene structure containing all scene elements.
 */
typedef struct s_scene
{
	int			fd;			/** File descriptor of the scene file. */
	t_ambient	ambient;	/** Ambient light settings. */
	t_camera	camera;		/** Camera settings. */
	t_light		*lights;	/** Linked list of lights in the scene. */
	t_object	*objects;	/**	Linked list of objects in the scene. */
}	t_scene;

// Parsing

bool	handle_argument(int ac, char **av);

// Utils

int		print_usage(void);
bool	errmsg(char *s1, char *s2, char *s3, bool status);

// Debug

void	print_scene(t_scene *s);

#endif