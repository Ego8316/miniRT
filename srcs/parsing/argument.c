/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:40:45 by ego               #+#    #+#             */
/*   Updated: 2025/06/15 17:11:26 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Handles the command-line arguments.
 */
bool	handle_argument(int ac, char **av)
{
	int	fd;

	if (ac < 2)
		return (errmsg(PREFIX, ERRMSG_NO_ARG, 0, false));
	if (ac > 2)
		return (errmsg(PREFIX, ERRMSG_TOO_ARG, 0, false));
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (errmsg(PREFIX, strerror(errno), 0, false));
	close(fd);
	return (true);
}
