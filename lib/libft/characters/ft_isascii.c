/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 07:27:10 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/14 17:59:06 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c);

/**
 * @brief Checks if a value is an ASCII character code.
 *
 * @param c Value to test.
 *
 * @return Non-zero if `c` is between 0 and 127, 0 otherwise.
 */
int	ft_isascii(int c)
{
	return (0 <= c && c <= 127);
}
