/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 14:57:42 by ego               #+#    #+#             */
/*   Updated: 2025/06/16 13:37:15 by ego              ###   ########.fr       */
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

/**
 * @brief Possible scene element identifiers.
 */
typedef enum e_identifier
{
	AMBIENT,		/** Ambient light */
	CAMERA,			/** Camera */
	LIGHT,			/** Light source */
	SPHERE,			/** Sphere object */
	PLANE,			/** Plane object */
	CYLINDER,		/** Cylinder object */
	CONE,			/** Cone object */
	HYPERBOLOID,	/** Hyperboloid object */
	PARABOLOID,		/** Paraboloid object */
	NONE			/** No identifier */
}	t_id;

// Structures

/**
 * @brief Dictionary entry linking string identifiers to enum and length.
 */
typedef struct s_dict
{
	const char	*string;	/** Identifier string */
	t_id		id;			/** Corresponding enum identifier */
	int			len;		/** Length of the string */
}	t_dict;

/**
 * @brief Boundaries structure for validating parsed values.
 */
typedef struct s_bound
{
	double		min;	/** Lower bound value. */
	double		max;	/** Upper bound value. */
	const char	*err;	/**	Error message to display. */
}	t_bound;

/**
 * @brief Parsing state data for a single line of the scene file.
 * 
 * Tracks the current line, parsing position, found identifiers, field count,
 * and error boundaries to validate input values.
 */
typedef struct s_parse_data
{
	bool		ambient_found;	/** `true` if ambient has been found */
	bool		camera_found;	/** `true` if camera has been found */
	char		*line;			/** Current line being parsed. */
	int			line_number;	/** Line number in the scene file. */
	int			i;				/** Current character index in the line. */
	t_id		id;				/** Current identifier found in the line. */
	int			field_count;	/** Number of data fields parsed. */
	t_bound		boundaries;		/**	Boundaries for the current parsed value. */
	bool		verbose;		/** Enables detailed parsing error messages. */
}	t_parse_data;

/**
 * @brief Color structure only for objects.
 */
typedef struct s_color
{
	bool	checkerboard;	/** `true` if the object is in checkerboard. */
	t_coor	coor;			/**	If not checkerboard, (R,G,B) color. */
}	t_color;

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
	t_ray	vector;	/** Position and direction of the camera. */
	double	fov;	/** Field of view of the camera in degrees. */
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
	t_id			id;				/** Type of the object. */
	t_coor			pos;			/** Position of the object. */
	t_coor			vector;			/**	Orientation vector (if applicable). */
	t_coor			args;			/**	Additional parameters. */
	double			reflectivity;	/**	Reflectivity coefficient. */
	t_color			color;			/** Color of the object. */
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
	const char	*filename;	/** Filename of the scene file. */
	t_ambient	ambient;	/** Ambient light settings. */
	t_camera	camera;		/** Camera settings. */
	t_light		*lights;	/** Linked list of lights in the scene. */
	t_object	*objects;	/**	Linked list of objects in the scene. */
}	t_scene;

// Parsing

bool	handle_argument(int ac, char **av);

double	ft_strtod(const char *str, char **endptr);
long	ft_strtol(const char *str, char **endptr, int base);

bool	get_next_double(t_parse_data *data, double *value, bool expect_comma);
bool	get_next_coordinate(t_parse_data *data, t_coor *coor);
bool	get_next_integer(t_parse_data *data, double *value, bool expect_comma);
bool	get_next_color(t_parse_data *data, t_coor *coor);
bool	get_next_object_color(t_parse_data *data, t_color *color);

char	*get_id_string(t_id id);
bool	get_identifier(t_parse_data *data);

bool	add_light(t_parse_data *data, t_scene *scene);

void	scale_color(t_coor *color);
bool	normalize_vector(t_coor *vec);

bool	parse_file(char *filename, t_scene *s);

void	init_parse_global_data(t_parse_data *data);
void	init_parse_line_data(t_parse_data *data);
void	skip_spaces(t_parse_data *data);
bool	ft_isspace(int c);
bool	stristype(const char *s, bool (*f)(int));

// Utils

int		print_usage(void);
bool	errmsg(char *s1, char *s2, char *s3, bool status);
bool	parse_errmsg(const char *error, t_parse_data *data);

bool	*free_str(char **s);
void	free_lights(t_light *lights);
void	free_lights(t_light *objects);
int		free_scene(t_scene *s);

// Debug

void	print_ambient(t_ambient *a);
void	print_light(t_light *l, int i);
void	print_lights(t_light **lights);
void	print_object(t_object *o, int i);
void	print_objects(t_object **objects);
void 	print_parse_data(t_parse_data *data);
void	print_camera(t_camera *c);
void	print_scene(t_scene *s);

#endif