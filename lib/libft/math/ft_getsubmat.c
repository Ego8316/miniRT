/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getsubmat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:28:05 by vviterbo          #+#    #+#             */
/*   Updated: 2025/06/20 16:13:19 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_mat	*ft_getsubmat(t_mat	mat, size_t m, size_t n);

/**
 * @brief Builds the submatrix excluding row m and column n.
 */
t_mat	*ft_getsubmat(t_mat	mat, size_t m, size_t n)
{
	t_mat	*submat;
	size_t	i;
	size_t	j;

	submat = ft_initmat(mat.dim[0] - 1, mat.dim[1] - 1);
	if (!submat)
		return (NULL);
	i = 0;
	while (i < mat.dim[0])
	{
		if (i == m)
			i++;
		j = 0;
		while (j < mat.dim[1])
		{
			if (j == n)
				j++;
			if (i >= mat.dim[0] || j >= mat.dim[1])
				break ;
			submat->val[i - (i > m)][j - (j > n)] = mat.val[i][j];
			j++;
		}
		i++;
	}
	return (submat);
}
