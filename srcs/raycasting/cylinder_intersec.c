/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersec.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 10:52:26 by vviterbo          #+#    #+#             */
/*   Updated: 2025/06/24 15:48:00 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_inter			*cylinder_intersec(t_object obj, t_ray ray);
// static t_inter	*local_intersec(t_ray ray);
// void			filter_w_bounds(t_inter *inter, t_object obj, t_ray);

/**
 * @brief Computes the intersection distances for a ray with an infinite
 * cylinder defined by `obj`. If no real solutions exist (ray misses the
 * cylinder sides), sets both of them to -1.
 * 
 * @param obj Cylinder object being tested.
 * @param ray Ray being cast.
 * @param t Array of two doubles to store the results.
 */
static void	get_infinite_side_hits(t_object obj, t_ray ray, double *t)
{
	double	dot[2];
	double	abc[3];
	double	discr;
	double	radius;
	t_coor	a;

	radius = obj.args[0] / 2;
	dot[0] = ft_dotprod(ray.dir, obj.vector);
	dot[1] = ft_dotprod(ft_coorsub(ray.orig, obj.pos), obj.vector);
	a = obj.vector;
	abc[0] = ft_squarenorm(ft_coorsub(ray.dir, ft_coormult(a, dot[0])));
	abc[1] = 2 * ft_dotprod(ft_coorsub(ray.dir, ft_coormult(a, dot[0])),
			ft_coorsub(ft_coorsub(ray.orig, obj.pos), ft_coormult(a, dot[1])));
	abc[2] = ft_squarenorm(ft_coorsub(ft_coorsub(ray.orig, obj.pos),
				ft_coormult(a, dot[1]))) - radius * radius;
	discr = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (discr < 0 || fabs(abc[0]) < DBL_EPSILON)
	{
		t[0] = -1;
		t[1] = -1;
		return ;
	}
	t[0] = (-abc[1] - sqrt(discr)) / (2 * abc[0]);
	t[1] = (-abc[1] + sqrt(discr)) / (2 * abc[0]);
	return ;
}

/**
 * @brief Adds valid side hits to the intersection structure. First gets all
 * hits with the infinite cylinder, and keeps the ones withint the finite
 * height of the cylinder.
 * 
 * @param obj Cylinder object.
 * @param ray Ray being cast.
 * @param inter Intersection structure to store the valid side hits.
 */
static void	add_side_hits(t_object obj, t_ray ray, t_inter *inter)
{
	double	t[2];
	double	height;
	t_coor	x;
	double	proj;
	int		i;

	get_infinite_side_hits(obj, ray, t);
	height = obj.args[1];
	i = -1;
	while (++i < 2)
	{
		if (t[i] < 0)
			continue ;
		x = ft_cooradd(ray.orig, ft_coormult(ray.dir, inter->inters[i]));
		proj = ft_dotprod(ft_coorsub(x, obj.pos), obj.vector);
		if (fabs(proj) < height / 2)
			inter->inters[inter->count++] = t[i];
	}
	return ;
}

/**
 * @brief Adds a valid cap hit to the intersection structure if the ray hits
 * one of the cylinder's.
 * 
 * @param obj Cylinder.
 * @param ray Ray.
 * @param inter Intersection structure.
 * @param c Coordinates for the center of the cap.
 */
static void	add_cap_hit(t_object obj, t_ray ray, t_inter *inter, t_coor c)
{
	double	radius;
	double	denom;
	double	t;
	t_coor	x;

	denom = ft_dotprod(obj.vector, ray.dir);
	if (fabs(denom) < DBL_EPSILON || inter->count == 2)
		return ;
	radius = obj.args[0] / 2;
	t = ft_dotprod(ft_coorsub(c, ray.orig), obj.vector) / denom;
	x = ft_cooradd(ray.orig, ft_coormult(ray.dir, t));
	if (ft_squarenorm(ft_coorsub(x, c)) <= radius * radius)
		inter->inters[inter->count++] = t;
	return ;
}

/**
 * @brief Computes all valid intersections (sides and caps) of a ray with a
 * finite cylinder.
 * 
 * @param obj Cylinder being tested.
 * @param ray Ray being cast.
 * 
 * @return Allocated intersection structure containing the valid hits, `NULL`
 * if memory allocation fails.
 */
t_inter	*cylinder_intersec(t_object obj, t_ray ray)
{
	t_inter	*inter;
	double	height;
	t_coor	bottom;
	t_coor	top;

	inter = ft_calloc(1, sizeof(t_inter));
	if (!inter)
		return (NULL);
	inter->inters = ft_calloc(2, sizeof(double));
	if (!inter->inters)
		return (free(inter), NULL);
	add_side_hits(obj, ray, inter);
	height = obj.args[1];
	bottom = ft_coormult(obj.vector, -1 * height / 2);
	top = ft_coormult(obj.vector, height / 2);
	add_cap_hit(obj, ray, inter, bottom);
	add_cap_hit(obj, ray, inter, top);
	inter->obj = &obj;
	return (inter);
}

// t_inter	*cylinder_intersec(t_object obj, t_ray ray)
// {
// 	t_ray	normal_ray;
// 	t_inter	*inter;

// 	(void)obj;
// 	normal_ray.orig = ray.orig;
// 	normal_ray.dir = ft_coornormalize(ray.dir);
// 	inter = local_intersec(normal_ray);
// 	if (!inter)
// 		return (NULL);
// 	filter_w_bounds(inter, obj, normal_ray);
// 	return (inter);
// }

// static t_inter	*local_intersec(t_ray ray)
// {
// 	t_inter	*inter;
// 	double	abc[3];
// 	double	discr;

// 	inter = ft_calloc(1, sizeof(t_inter));
// 	if (!inter)
// 		return (NULL);
// 	abc[0] = ray.dir.x * ray.dir.x + ray.dir.z * ray.dir.z;
// 	if (abc[0] < DBL_EPSILON)
// 		return (inter);
// 	abc[1] = 2 * ray.orig.x * ray.dir.x + 2 * ray.orig.z * ray.dir.z;
// 	abc[2] = ray.orig.x * ray.orig.x + ray.orig.z * ray.orig.z - 1;
// 	discr = abc[1] * abc[1] - 4 * abc[0] * abc[2];
// 	if (discr < 0)
// 		return (inter);
// 	inter->inters = ft_calloc(2, sizeof(double));
// 	if (!inter->inters)
// 		return (free(inter), NULL);
// 	inter->inters[0] = (-abc[1] - sqrt(discr)) / (2 * abc[0]);
// 	inter->inters[1] = (-abc[1] + sqrt(discr)) / (2 * abc[0]);
// 	if (inter->inters[0] > inter->inters[1])
// 		ft_swap_dble(&(inter->inters[0]), &(inter->inters[1]));
// 	inter->count = 2;
// 	return (inter);
// }

// void	filter_w_bounds(t_inter *inter, t_object obj, t_ray ray)
// {
// 	double	y;
// 	size_t	i;
// 	size_t	n;

// 	n = 0;
// 	while (n < inter->count)
// 	{
// 		y = ray.orig.y + inter->inters[n] * ray.dir.y;
// 		if (y < - obj.args[HEIGHT] / 2 || y > obj.args[HEIGHT] / 2)
// 		{
// 			i = n;
// 			while (i < inter->count - 1)
// 			{
// 				inter->inters[i] = inter->inters[i + 1];
// 				i++;
// 			}
// 			inter->count = inter->count - 1;
// 		}
// 		else
// 			n += 1;
// 	}
// }
