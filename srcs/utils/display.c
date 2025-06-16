/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:26:08 by ego               #+#    #+#             */
/*   Updated: 2025/06/16 19:05:34 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Prints a double-precision floating-point number to a file descriptor
 * up to `precision` decimal digits. Only used to display bound values for
 * parsing errors.
 * 
 * @param nbr The double value to print.
 * @param precision Number of decimal places to print.
 * @param fd File descriptor where the output is written.
 */
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
