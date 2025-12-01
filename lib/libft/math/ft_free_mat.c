/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_mat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:52:14 by vviterbo          #+#    #+#             */
/*   Updated: 2025/06/10 15:54:17 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_mat(t_mat *mat);

/**
 * @brief Frees a matrix allocated by ft_initmat.
 */
void	ft_free_mat(t_mat *mat)
{
	size_t	i;

	i = 0;
	while (i < mat->dim[0])
	{
		free(mat->val[i]);
		i++;
	}
	free(mat);
	return ;
}
