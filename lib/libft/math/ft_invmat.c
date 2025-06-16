/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_invmat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:26:45 by vviterbo          #+#    #+#             */
/*   Updated: 2025/06/16 11:29:31 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_mat	*ft_invmat(t_mat mat)
{
	t_mat	*inv;
	double	*det;
	double	*cofac;
	size_t	i;
	size_t	j;

	if (mat.dim[0] != mat.dim[1])
		return (NULL);
	det = ft_detmat(mat);
	if (!det || !*det)
		return (NULL);
	inv = ft_initmat(mat.dim[0], mat.dim[1]);
	if (!inv)
		return (NULL);
	i = 0;
	while (i < mat.dim[0])
	{
		j = 0;
		while (j < mat.dim[1])
		{
			cofac = ft_getcofac(mat, i, j);
			if (!cofac)
				return (ft_free_mat(inv), NULL);
			inv->val[j][i] = mat.val[i][j] * *cofac / *det;
			j++;
		}
		i++;
	}
	return (inv);
}
