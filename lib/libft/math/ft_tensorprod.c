/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tensorprod.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 17:06:23 by ego               #+#    #+#             */
/*   Updated: 2025/06/20 17:07:20 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_coor	ft_tensorprod(t_coor v1, t_coor v2);

/**
 * @brief Computes element-wise (Hadamard) product of two vectors.
 */
t_coor	ft_tensorprod(t_coor v1, t_coor v2)
{
	t_coor	tensor_prod;

	tensor_prod.x = v1.x * v2.x;
	tensor_prod.y = v1.y * v2.y;
	tensor_prod.z = v1.z * v2.z;
	return (tensor_prod);
}
