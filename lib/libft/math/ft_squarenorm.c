/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_squarenorm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 17:13:12 by ego               #+#    #+#             */
/*   Updated: 2025/06/20 17:13:33 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_squarenorm(t_coor coor);

/**
 * @brief Returns squared magnitude of a 3D vector.
 */
double	ft_squarenorm(t_coor coor)
{
	double	norm;

	norm = coor.x * coor.x + coor.y * coor.y + coor.z * coor.z;
	return (norm);
}
