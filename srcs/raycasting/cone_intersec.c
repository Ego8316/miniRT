/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_intersec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 12:40:50 by ego               #+#    #+#             */
/*   Updated: 2025/06/25 14:48:02 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_inter	cone_intersec(t_object obj, t_ray ray);

/**
 * @brief Computes the intersection distances for a ray with an infinite cone
 * defined by `obj`. If no real solutions exist (ray misses the cone sides),
 * sets both of them to -1.
 * 
 * @param obj Cone object being tested.
 * @param ray Ray being cast.
 * @param t Array of two doubles to store the results.
 */
static void	get_infinite_side_hits(t_object obj, t_ray ray, double *t)
{
	double	dot[2];
	double	abc[3];
	double	discr;
	double	squared_cos;

	squared_cos = 1 / (1 + pow(obj.args[0] / (2 * obj.args[1]), 2));
	dot[0] = ft_dotprod(ray.dir, obj.vector);
	dot[1] = ft_dotprod(ft_coorsub(ray.orig, obj.pos), obj.vector);
	abc[0] = dot[0] * dot[0] - squared_cos;
	abc[1] = -2 * (squared_cos * ft_dotprod(ft_coorsub(ray.orig, obj.pos),
				ray.dir) - dot[0] * dot[1]);
	abc[2] = dot[1] * dot[1] - squared_cos * ft_squarenorm(ft_coorsub(ray.orig,
				obj.pos));
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
 * hits with the infinite cone, and keeps the ones withint the finite height
 * of the actual cone.
 * 
 * @param obj Cone object.
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
		x = ft_cooradd(ray.orig, ft_coormult(ray.dir, t[i]));
		proj = ft_dotprod(ft_coorsub(x, obj.pos), obj.vector);
		if (proj > DBL_EPSILON && proj < height)
			inter->t[inter->count++] = t[i];
	}
	return ;
}

/**
 * @brief Adds a valid cap hit to the intersection structure if the ray hits
 * one of the cone's.
 * 
 * @param obj Cone.
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
		inter->t[inter->count++] = t;
	return ;
}

/**
 * @brief Computes all valid intersections (sides and caps) of a ray with a
 * finite cone.
 * 
 * @param obj Cone being tested.
 * @param ray Ray being cast.
 * 
 * @return Allocated intersection structure containing the valid hits, `NULL`
 * if memory allocation fails.
 */
t_inter	cone_intersec(t_object obj, t_ray ray)
{
	t_inter	inter;
	t_coor	base;

	add_side_hits(obj, ray, &inter);
	base = ft_cooradd(obj.pos, ft_coormult(obj.vector, obj.args[1]));
	add_cap_hit(obj, ray, &inter, base);
	return (inter);
}
