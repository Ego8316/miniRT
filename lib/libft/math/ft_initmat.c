/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initmat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:34:23 by vviterbo          #+#    #+#             */
/*   Updated: 2025/06/16 11:28:36 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_mat	*ft_initmat(size_t m, size_t n)
{
	t_mat	*mat;
	size_t	i;

	mat = ft_calloc(1, sizeof(t_mat));
	mat->val = ft_calloc(m, sizeof(double *));
	if (!mat->val)
		return (NULL);
	i = 0;
	while (i < n)
	{
		mat->val[i] = ft_calloc(m, sizeof(double));
		if (!mat->val[i])
		{
			while (i)
			{
				free(mat->val[i - 1]);
				i--;
			}
			return (free(mat->val), free(mat), NULL);
		}
		i++;
	}
	return (mat);
}
