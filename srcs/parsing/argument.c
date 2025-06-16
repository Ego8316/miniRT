/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:40:45 by ego               #+#    #+#             */
/*   Updated: 2025/06/16 17:17:41 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Validates the program's command-line argument as readable file.
 * 
 * Ensures that the argument count is exactly 2, attempts to open the alleged
 * file in read-only mode, and ensures that the file is readable and not empty.
 * 
 * If any check fails, a descriptive error message is printed with `errmsg`.
 * 
 * @param ac Argument count.
 * @param av Argument vector.
 * 
 * @return `true` if the argument is valid, the file exists, is readable and
 * non-empty; `false` otherwise.
 */
bool	handle_argument(int ac, char **av)
{
	int		fd;
	ssize_t	r;
	char	buf[1];

	if (ac < 2)
		return (errmsg(ERRMSG_NO_ARG, 0, 0, false));
	if (ac > 2)
		return (errmsg(ERRMSG_TOO_ARG, 0, 0, false));
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (errmsg(av[1], ": ", strerror(errno), false));
	r = read(fd, buf, 1);
	close(fd);
	if (r == 0)
		return (errmsg(av[1], ": ", ERRMSG_EMPTY_FILE, false));
	if (r < 0)
		return (errmsg(av[1], ": ", strerror(errno), false));
	return (true);
}
