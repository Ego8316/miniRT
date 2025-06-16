/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:40:25 by vviterbo          #+#    #+#             */
/*   Updated: 2025/06/12 01:36:41 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_ray	initray(double orig[3], double dir[3]);

t_ray	initray(double origin[3], double direction[3])
{
	t_ray	ray;

	ray.dir = ft_initcoor(origin[0], origin[1], origin[2]);
	ray.dir = ft_initcoor(direction[0], direction[1], direction[2]);
	return (ray);
}
