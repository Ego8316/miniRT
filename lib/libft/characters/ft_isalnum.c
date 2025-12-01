/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 07:25:20 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/14 17:57:35 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c);

/**
 * @brief Checks if a character is alphanumeric.
 *
 * @param c Character to test.
 *
 * @return Non-zero if `c` is a letter or digit, 0 otherwise.
 */
int	ft_isalnum(int c)
{
	return (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z')
		|| ('0' <= c && c <= '9'));
}
