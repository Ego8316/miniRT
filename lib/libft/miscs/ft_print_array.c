/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:09:07 by vviterbo          #+#    #+#             */
/*   Updated: 2025/12/01 01:06:12 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_array(char **arr, bool nl);

/**
 * @brief Prints each string in a NULL-terminated array, optionally
 * newline-separated.
 */
void	ft_print_array(char **arr, bool nl)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		if (nl)
			ft_printf("%s\n", arr[i]);
		else
			ft_printf("%s", arr[i]);
		i++;
	}
	return ;
}
