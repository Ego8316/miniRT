/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_invmat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:26:45 by vviterbo          #+#    #+#             */
/*   Updated: 2025/06/20 18:48:49 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdio.h>

t_mat	*ft_invmat(t_mat mat);

t_mat	*ft_invmat(t_mat mat)
{
	t_mat	*inv;
	double	*det;
	double	*cofac;
	size_t	i;

	det = ft_detmat(mat);
	if (!det || !*det)
		return (NULL);
	inv = ft_initmat(mat.dim[0], mat.dim[1]);
	if (!inv)
		return (NULL);
	i = 0;
	while (i < mat.dim[0] * mat.dim[1])
	{
		cofac = ft_getcofac(mat, i / mat.dim[0], i % mat.dim[0]);
		if (!cofac)
			return (ft_free_mat(inv), NULL);
		inv->val[i % mat.dim[0]][i / mat.dim[0]] = *cofac / *det;
		i++;
	}
	return (inv);
}
