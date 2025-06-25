/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printmat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 12:03:37 by vviterbo          #+#    #+#             */
/*   Updated: 2025/06/25 14:46:11 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	ft_printmat(t_mat mat);

void	ft_printmat(t_mat mat)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < mat.dim[0])
	{
		j = 0;
		while (j < mat.dim[1])
		{
			printf("%f", mat.val[i][j]);
			if (j + 1 < mat.dim[1])
				printf(", ");
			else
				printf("\n");
			j++;
		}
		i++;
	}
	return ;
}
