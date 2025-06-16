/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initcoor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:23:36 by vviterbo          #+#    #+#             */
/*   Updated: 2025/06/16 11:52:28 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_coor	ft_initcoor(double x, double y, double z);

t_coor	ft_initcoor(double x, double y, double z)
{
	t_coor	new_coor;

	new_coor.x = x;
	new_coor.y = y;
	new_coor.z = z;
	return (new_coor);
}
