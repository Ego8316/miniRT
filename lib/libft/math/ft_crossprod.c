/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_crossprod.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:36:48 by ego               #+#    #+#             */
/*   Updated: 2025/06/20 16:39:44 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_coor	ft_crossprod(t_coor v1, t_coor v2);

t_coor	ft_crossprod(t_coor v1, t_coor v2)
{
	t_coor	cross_prod;

	cross_prod.x = v1.y * v2.z - v1.z * v2.y;
	cross_prod.y = v1.z * v2.x - v1.x * v2.z;
	cross_prod.z = v1.x * v2.y - v1.y * v2.x;
	return (cross_prod);
}
