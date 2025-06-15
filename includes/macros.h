/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:19:42 by ego               #+#    #+#             */
/*   Updated: 2025/06/15 17:28:25 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

// Colors

# define COLOR_R "\033[31m"
# define COLOR_O "\033[38;5;214m"
# define COLOR_Y "\033[33m"
# define COLOR_G "\033[32m"
# define COLOR_B "\033[34m"
# define COLOR_V "\033[38;5;93m"
# define C_RESET "\033[0m"

// Error messages

# define USAGE_MSG "Usage: ./minirt <scene.rt>"
# define PREFIX "minirt: "
# define ERRMSG_NO_ARG "need argument"
# define ERRMSG_TOO_ARG "too many arguments"
# define ERRMSG_EMPTY_FILE "file is empty"

#endif