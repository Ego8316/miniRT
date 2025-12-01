/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:55:55 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/20 19:01:12 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	*ft_range(int min, int max);

/**
 * @brief Allocates an int array with values [min, max).
 */
int	*ft_range(int min, int max)
{
	int	*range;
	int	i;

	if (max < min || max - min > INT_MAX)
		return (NULL);
	range = ft_calloc(max - min, sizeof(int));
	if (!range)
		return (NULL);
	i = 0;
	while (min != max)
	{
		range[i] = min;
		min++;
		i++;
	}
	return (range);
}
