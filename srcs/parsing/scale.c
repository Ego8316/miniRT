/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 05:49:41 by ego               #+#    #+#             */
/*   Updated: 2025/06/16 05:51:49 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Scales a color vector from 0-255 range to 0.0-1.0 range.
 * 
 * @param color Pointer to the color vector to scale.
 */
void	scale_color(t_coor *color)
{
	*color = ft_coorscale((t_coor){0, 0, 0}, *color, 1.0 / 255.0);
	return ;
}

/**
 * @brief Normalizes a vector in-place if its norm is non-zero.
 * 
 * Computes the Euclidean norm of the given vector and scales it to have unit
 * length. If the vector has a norm close to zero (within `DBL_EPSILON`),
 * normalization is not performed.
 * 
 * @param vec Pointer to the vector to normalize.
 * 
 * @return `true` if the vector was successfully normalized, `false` if the
 * vector has zero (or near-zero) norm.
 */
bool	normalize_vector(t_coor *vec)
{
	double	norm;

	norm = ft_norm(*vec);
	if (norm < DBL_EPSILON)
		return (false);
	*vec = ft_coorscale((t_coor){0, 0, 0}, *vec, 1 / norm);
	return (true);
}
