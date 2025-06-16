/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_coorscale.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:23:25 by vviterbo          #+#    #+#             */
/*   Updated: 2025/06/16 11:51:40 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_coor	ft_coorscale(t_coor base, t_coor tip, float scale);

t_coor	ft_coorscale(t_coor base, t_coor tip, float scale)
{
	t_coor	new_coor;

	new_coor.x = (tip.x - base.x) * (double)scale + base.x;
	new_coor.y = (tip.y - base.y) * (double)scale + base.y;
	new_coor.z = (tip.z - base.z) * (double)scale + base.z;
	return (new_coor);
}
