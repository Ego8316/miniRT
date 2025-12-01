/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matcoor_mult.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 14:45:10 by vviterbo          #+#    #+#             */
/*   Updated: 2025/06/20 15:02:27 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_coor	matcoor_mult(t_mat mat, t_coor vec);

/**
 * @brief Multiplies a 3x3 matrix by a coordinate vector.
 */
t_coor	matcoor_mult(t_mat mat, t_coor vec)
{
	t_coor	mult;
	size_t	i;

	if (mat.dim[1] != 3)
	{
		mult.x = 0;
		mult.y = 0;
		mult.z = 0;
		return (mult);
	}
	mult.x = mat.val[0][0] * vec.x + mat.val[0][1] * vec.y
		+ mat.val[0][2] * vec.z;
	mult.y = mat.val[1][0] * vec.x + mat.val[1][1] * vec.y
		+ mat.val[1][2] * vec.z;
	mult.z = mat.val[2][0] * vec.x + mat.val[2][1] * vec.y
		+ mat.val[2][2] * vec.z;
	return (mult);
}
