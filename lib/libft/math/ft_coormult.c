/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_coormult.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 17:07:56 by ego               #+#    #+#             */
/*   Updated: 2025/06/20 17:09:05 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_coor	ft_coormult(t_coor v, double lambda);

t_coor	ft_coormult(t_coor v, double lambda)
{
	t_coor	new_coor;

	new_coor.x = v.x * lambda;
	new_coor.y = v.y * lambda;
	new_coor.z = v.z * lambda;
	return (new_coor);
}
