/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap_dble.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:52:13 by vviterbo          #+#    #+#             */
/*   Updated: 2025/06/20 11:53:36 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_swap_dble(double *x, double *y);

void	ft_swap_dble(double *x, double *y)
{
	double tmp;

	tmp = *x;
	*x = *y;
	*y = tmp;
	return ;
}
