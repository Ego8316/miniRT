/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victorviterbo <victorviterbo@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 14:57:42 by ego               #+#    #+#             */
/*   Updated: 2025/09/10 14:43:32 by victorviter      ###   ########.fr       */
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
# ifdef __APPLE__
#  include "../lib/minilibx-macos/mlx.h"
# else
#  include "../lib/minilibx-linux/mlx.h"
# endif

/* Enums */

typedef enum e_identifier
{
	AMBIENT,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER,
	CONE,
	NONE
}	t_id;

typedef enum e_cycl_args
{
	DIAMETER,
	HEIGHT
}	t_cycl_args;

typedef enum e_cone_args
{
	ANGLE,
}	t_cone_args;

/* Structures */

typedef struct s_dict
{
	const char	*string;
	t_id		id;
	int			len;
}	t_dict;

typedef struct s_bound
{
	double		min;
	double		max;
	const char	*err;
}	t_bound;

typedef struct s_args
{
	t_id	id;
	t_bound	arg_bounds[3];
}	t_args;

typedef struct s_attribute
{
	double		*value;
	const char	*id;
	bool		found;
	const char	*dup_err;
	t_bound		bound;
}	t_attribute;

typedef struct s_parse_data
{
	bool		ambient_found;
	bool		camera_found;
	char		*line;
	int			line_number;
	int			i;
	t_id		id;
	t_bound		boundaries;
	bool		verbose;
}	t_parse_data;

typedef struct s_color
{
	t_coor	coor;
	bool	checkerboard;
	bool	textured;
	t_coor	**texture;
	double	**bump;
}	t_color;

typedef struct s_ambient
{
	double	ratio;
	t_coor	color;
}	t_ambient;

typedef struct s_camera
{
	t_ray	vector;
	double	fov;
}	t_camera;

typedef struct s_light
{
	t_coor			pos;
	double			brightness;
	t_coor			color;
	struct s_light	*next;
}	t_light;

typedef struct s_object
{
	t_id			id;
	t_coor			pos;
	t_coor			vector;
	double			args[MAX_ARGS];
	t_color			color;
	double			specular;
	double			bump_strength;
	struct s_object	*next;
}	t_object;

typedef struct s_scene
{
	int			fd;
	const char	*filename;
	t_ambient	ambient;
	t_camera	camera;
	t_light		*lights;
	t_object	*objects;
}	t_scene;

typedef struct s_imgdata
{
	void		*img;
	void		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}	t_imgdata;

typedef struct s_imx
{
	void		*mlx;
	void		*win;
	t_imgdata	*img;
	t_coor		size;
	t_scene		*scene;
}	t_imx;

typedef struct s_view
{
	t_coor	f;
	t_coor	r;
	t_coor	u;
	t_coor	orig;
	t_coor	size;
	double	h_width;
	double	h_height;
}	t_view;

typedef struct s_inter
{
	size_t		count;
	t_object	*obj;
	double		t[2];
}	t_inter;

typedef struct s_uv
{
	double	u;
	double	v;
}	t_uv;

typedef struct s_hit
{
	t_coor		point;
	t_inter		inter;
	t_coor		color;
	t_coor		normal;
	t_coor		ray;
	t_coor		tangent_u;
	t_coor		tangent_v;
	t_uv		uv;
}	t_hit;

/* Parsing */

bool	handle_argument(int ac, char **av);
double	ft_strtod(const char *str, char **endptr);
long	ft_strtol(const char *str, char **endptr, int base);
bool	get_next_double(t_parse_data *d, double *v, bool comma, bool verb);
bool	get_next_coordinate(t_parse_data *data, t_coor *coor);
bool	get_next_integer(t_parse_data *data, double *value, bool expect_comma);
bool	get_next_color(t_parse_data *data, t_coor *coor);
bool	get_next_object_color(t_parse_data *data, t_color *color);
bool	load_texture(char *word, t_color *color);
bool	load_bump(char *word, t_color *color);
bool	free_texture(t_coor ***texture);
bool	free_bump(double ***bump);

char	*get_id_string(t_id id);
bool	get_identifier(t_parse_data *data);

bool	add_light(t_parse_data *data, t_scene *scene);
bool	add_object(t_parse_data *data, t_scene *scene);

bool	init_scene(char *filename, t_scene *s);

bool	get_next_word(t_parse_data *data, char *word, int *word_start);
void	skip_spaces(t_parse_data *data);
bool	trailing_data(t_parse_data *data);
void	add_light_to_list(t_light *new, t_light **lights);
void	add_object_to_list(t_object *new, t_object **objects);
bool	get_attribute(t_parse_data *d, t_attribute *a, int i, const char *w);

/* Utils */

double	ft_clamp(double val, double min, double max);
void	scale_color(t_coor *color);
bool	normalize_vector(t_coor *vec);

bool	errmsg(char *s1, char *s2, char *s3, bool status);
bool	parse_errmsg(const char *err, t_parse_data *d, bool verb, bool bound);
void	ft_putdouble_fd(double nbr, int precision, int fd);

bool	*free_str(char **s);
void	free_lights(t_light *lights);
void	free_objects(t_object *objects);
int		free_scene(t_scene *s);

bool	ft_isspace(int c);
bool	stristype(const char *s, bool (*f)(int));

/* Ray Casting */

t_inter	cone_intersec(t_object *obj, t_ray ray);
t_inter	get_inter(t_object *obj, t_ray ray);
t_inter	plane_intersec(t_object *obj, t_ray ray);
t_inter	cylinder_intersec(t_object *obj, t_ray ray);
t_inter	sphere_intersec(t_object *obj, t_ray ray);

int		color_to_rgb(t_coor color);
t_coor	get_object_color(t_object *obj, t_hit *hit);
t_coor	get_normal(t_hit hit);
int		get_inter_color(t_scene scene, t_inter inter, t_ray view);
bool	is_shadowed(t_scene s, t_coor light, t_inter objinter, t_ray view);
t_uv	get_cylinder_cap_uv(t_object *cyl, t_hit *hit, bool top);
t_uv	get_cylinder_side_uv(t_object *cyl, t_hit *hit);
t_uv	get_cone_cap_uv(t_object *cone, t_hit *hit);
t_uv	get_cone_side_uv(t_object *cone, t_hit *hit);
t_uv	get_uv(t_object *obj, t_hit *hit);
t_coor	get_bump_normal(t_coor original_normal, t_hit hit);

/* Graphix */

bool	init_window(t_imx *window, size_t size_x, size_t size_y);
void	display_scene(t_imx *window);
void	project_scene(t_scene, t_imx *window);
t_inter	get_first_inter(t_scene scene, t_ray view);
t_coor	get_viewdir(t_view viewbase, t_coor curr_pxl);
t_view	ft_init_view(t_scene scene, t_coor screensize);
int		free_win(t_imx *imx);
int		clean_exit(t_imx *imx);

/* Debug */

void	print_ambient(t_ambient *a);
void	print_light(t_light *l, int i);
void	print_lights(t_light **lights);
void	print_object(t_object *o, int i);
void	print_objects(t_object **objects);
void	print_parse_data(t_parse_data *data);
void	print_camera(t_camera *c);
void	print_scene(t_scene *s);

#endif
