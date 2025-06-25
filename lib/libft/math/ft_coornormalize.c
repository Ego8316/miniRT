/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_coornormalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:16:57 by vviterbo          #+#    #+#             */
/*   Updated: 2025/06/25 19:41:19 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_coor	ft_coornormalize(t_coor coor);

t_coor	ft_coornormalize(t_coor coor)
{
	double	norm_fac;
	t_coor	normal;

	norm_fac = 1.0 / sqrt(ft_dotprod(coor, coor));
	normal.x = coor.x * norm_fac;
	normal.y = coor.y * norm_fac;
	normal.z = coor.z * norm_fac;
	return (normal);
}
