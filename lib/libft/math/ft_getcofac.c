/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getcofac.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 11:11:27 by vviterbo          #+#    #+#             */
/*   Updated: 2025/06/20 17:27:14 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	*ft_getcofac(t_mat mat, int m, int n);

double	*ft_getcofac(t_mat mat, int m, int n)
{
	t_mat	*submat;
	double	*subdet;

	submat = ft_getsubmat(mat, m, n);
	if (!submat)
		return (NULL);
	subdet = ft_detmat(*submat);
	ft_free_mat(submat);
	if (subdet && (m + n) % 2)
		*subdet = -*subdet;
	return (subdet);
}
