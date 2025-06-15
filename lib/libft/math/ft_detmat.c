/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_detmat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:13:06 by vviterbo          #+#    #+#             */
/*   Updated: 2025/06/15 16:31:26 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	*ft_detmat(t_mat mat);
double	*ft_detmat22(t_mat mat);

double	*ft_detmat(t_mat mat)
{
	double	det;
	double	*subdet;
	size_t	i;

	if (mat.dim[0] != mat.dim[1])
		return (NULL);
	if (mat.dim[0] == 2)
		return (ft_detmat22(mat));
	i = 0;
	while (i < mat.dim[0])
	{
		subdet = ft_getcofac(mat, 0, i);
		if (!subdet)
			return (NULL);
		det += mat.val[0][i] * *subdet;
		i++;
	}
	return (&det);
}

double	*ft_detmat22(t_mat mat)
{
	double	det;

	if (mat.dim[0] != 2 || mat.dim[1] != 2)
		return (NULL);
	det = mat.val[0][0] * mat.val[1][1] - mat.val[1][0] * mat.val[0][1];
	return (&det);
}
