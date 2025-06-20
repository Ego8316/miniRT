/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matmult.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:06:17 by vviterbo          #+#    #+#             */
/*   Updated: 2025/06/20 15:16:18 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_mat	*ft_matmult(t_mat mat1, t_mat mat2);

t_mat	*ft_matmult(t_mat mat1, t_mat mat2)
{
	t_mat	*mult;
	size_t	i;
	size_t	j;
	size_t	k;

	if (mat1.dim[1] != mat2.dim[0])
		return (NULL);
	mult = ft_initmat(mat1.dim[0], mat2.dim[1]);
	if (!mult)
		return (NULL);
	i = 0;
	while (i < mat1.dim[0])
	{
		j = 0;
		while (j < mat2.dim[1])
		{
			k = 0;
			while (++k < mat1.dim[1])
				mult->val[i][j] += mat1.val[i][k] * mat2.val[k][j];
			j++;
		}
		i++;
	}
	return (mult);
}
