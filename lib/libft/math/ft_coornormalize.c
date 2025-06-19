/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_coornormalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:16:57 by vviterbo          #+#    #+#             */
/*   Updated: 2025/06/18 11:19:51 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_coor	ft_coornormalize(t_coor coor);

t_coor	ft_coornormalize(t_coor coor)
{
	double	norm_fac;
	t_coor	normal;

	norm_fac = 1/ sqrt(ft_dotprod(coor, coor));
	normal.x = coor.x * norm_fac;
	normal.y = coor.y * norm_fac;
	normal.z = coor.z * norm_fac;
	return (normal);
}
