/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:46:12 by ego               #+#    #+#             */
/*   Updated: 2025/06/15 17:11:49 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Displays the usage help message and returns 1.
 * 
 * @return 1.
 */
int	print_usage(void)
{
	printf("%s%s%s\n", COLOR_B, USAGE_MSG, C_RESET);
	return (1);
}

/**
 * @brief Prints on the standard error up to three strings and returns the
 * given bool.
 * 
 * @param s1 First string to be printed.
 * @param s2 Second string to be printed.
 * @param s3 Third string to be printed.
 * @param status Status to return.
 * 
 * @return `status`.
 */
bool	errmsg(char *s1, char *s2, char *s3, bool status)
{
	ft_putstr_fd(COLOR_R, STDERR_FILENO);
	if (s1)
		ft_putstr_fd(s1, STDERR_FILENO);
	if (s2)
		ft_putstr_fd(s2, STDERR_FILENO);
	if (s3)
		ft_putstr_fd(s3, STDERR_FILENO);
	ft_putstr_fd(C_RESET, STDERR_FILENO);
	return (status);
}
