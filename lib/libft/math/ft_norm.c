/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_norm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:10:02 by vviterbo          #+#    #+#             */
/*   Updated: 2025/06/09 17:21:33 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>

double	ft_norm(t_coor coor);

/**
 * @brief Computes the Euclidean norm of a 3D vector.
 */
double	ft_norm(t_coor coor)
{
	double	norm;

	norm = sqrt(coor.x * coor.x + coor.y * coor.y
			+ coor.z * coor.z);
	return (norm);
}
