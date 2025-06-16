/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:26:08 by ego               #+#    #+#             */
/*   Updated: 2025/06/16 16:45:36 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_putdouble_fd(double nbr, int precision, int fd)
{
	int		integer_part;
	double	frac;

	integer_part = (long)nbr;
	frac = nbr - integer_part;
	if (frac < 0)
		frac *= -1;
	ft_putnbr_fd(integer_part, fd);
	if (frac < DBL_EPSILON)
		return ;
	ft_putchar_fd('.', fd);
	while (precision-- > 0)
	{
		frac *= 10;
		ft_putchar_fd((long)frac + '0', fd);
		frac -= (long)frac;
	}
	return ;
}
