/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cooradd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 11:52:09 by vviterbo          #+#    #+#             */
/*   Updated: 2025/06/16 11:52:15 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_coor	ft_cooradd(t_coor v1, t_coor v2);

t_coor	ft_cooradd(t_coor v1, t_coor v2)
{
	t_coor	new_coor;

	new_coor.x = v1.x + v2.x;
	new_coor.y = v1.y + v2.y;
	new_coor.z = v1.z + v2.z;
	return (new_coor);
}
