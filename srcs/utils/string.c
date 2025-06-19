/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 18:08:22 by ego               #+#    #+#             */
/*   Updated: 2025/06/16 18:08:29 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Checks if a string is only made of one given type.
 * 
 * @param s String to be checked.
 * @param f Function used to check the type (isspace for example).
 * 
 * @return `true` if it is only made of the given type, `false` otherwise.
 */
bool	stristype(const char *s, bool (*f)(int))
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!f(s[i]))
			return (false);
		i++;
	}
	return (true);
}

/** 
 * @brief Checks if a character is a space.
 * 
 * @param c The character to check.
 * 
 * @return 1 if the character is a space, 0 otherwise.
 */
bool	ft_isspace(int c)
{
	return ((9 <= c && c <= 13) || c == 32);
}
