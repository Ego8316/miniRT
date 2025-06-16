/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:19:42 by ego               #+#    #+#             */
/*   Updated: 2025/06/16 16:44:37 by ego              ###   ########.fr       */
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

// Identifiers
# define AMBIENT_ID "A"
# define CAMERA_ID "C"
# define LIGHT_ID "L"
# define SPHERE_ID "sp"
# define PLANE_ID "pl"
# define CYLINDER_ID "cy"
# define CONE_ID "co"
# define HYPERBOLOID_ID "hy"
# define PARABOLOID_ID "pa"
# define SETTING_ID_SIZE 1
# define OBJECT_ID_SIZE 2

// Max values
# define COLOR_MIN 0.0
# define COLOR_MAX 255.0
# define COORD_MIN -1000.0
# define COORD_MAX 1000.0
# define VECT_MIN -1.0
# define VECT_MAX 1.0
# define BRIGHTNESS_MIN 0.0
# define BRIGHTNESS_MAX 1.0
# define FOV_MIN 0.0
# define FOV_MAX 180.0
# define SP_DIAMETER_MIN 0.1
# define SP_DIAMETER_MAX 1000.0
# define CY_DIAMETER_MIN 0.1
# define CY_DIAMETER_MAX 500.0
# define CY_HEIGHT_MIN 0.001
# define CY_HEIGHT_MAX 1000.0
# define CO_ANGLE_MIN 0.1
# define CO_ANGLE_MAX 179.9
# define PA_K_MIN 0.1
# define PA_K_MAX 100.0
# define HY_A_MIN 0.1
# define HY_A_MAX 500.0
# define HY_C_MIN 0.1
# define HY_C_MAX 500.0

// Syntax keywords
# define CHECKERBOARD "checkerboard"
# define CHECKERBOARD_SIZE 12

// Error messages

# define USAGE_MSG "Usage: ./minirt <scene.rt>"
# define PREFIX "minirt: "
# define VERBOSE_PREFIX "line : "
# define ERRMSG_NO_ARG "need argument"
# define ERRMSG_TOO_ARG "too many arguments"
# define ERRMSG_EMPTY_FILE "file is empty"
# define ERRMSG_MALLOC "malloc: allocation failed"

// Parsing error messages

# define PARSE_ERR_UNKNOWN_IDENTIFIER "identifier does not match known types"
# define PARSE_ERR_AMBIENT_DUPLICATE "duplicate ambient lighting definition"
# define PARSE_ERR_CAMERA_DUPLICATE "duplicate camera definition"

# define PARSE_ERR_UNEXPECTED_COMMA "unexpected comma"
# define PARSE_ERR_EXPECTED_COMMA "expected comma"
# define PARSE_ERR_EXPECTED_DOUBLE "expected double number"
# define PARSE_ERR_EXPECTED_INTEGER "expected integer number"

# define PARSE_ERR_TOO_FEW_ARGUMENTS "not enough data fields after identifier"
# define PARSE_ERR_TOO_MANY_ARGUMENTS "more than expected data fields"
# define PARSE_ERR_EXTRA_DATA "unexpected trailing data after valid fields"

# define PARSE_ERR_INVALID_COLOR "invalid color, expected `checkerboard'"
# define PARSE_ERR_BOUND "out of range"
# define PARSE_ERR_BOUND_COLOR "color value"
# define PARSE_ERR_BOUND_COORD "coordinate"
# define PARSE_ERR_BOUND_BRIGHTNESS "brightness value"
# define PARSE_ERR_BOUND_FOV "fov value"
# define PARSE_ERR_BOUND_SP_RAD "sphere diameter"
# define PARSE_ERR_BOUND_CY_RAD "cylinder diameter"
# define PARSE_ERR_BOUND_CY_HEIGHT "cylinder height"
# define PARSE_ERR_BOUND_CO_ANGLE "cone angle"
# define PARSE_ERR_BOUND_PA_SPREAD "paraboloid spread value"
# define PARSE_ERR_BOUND_HY_RADIAL "hyperboloid radial value"
# define PARSE_ERR_BOUND_HY_VERTICAL "hyperboloid vertical value"
# define PARSE_ERR_BOUND_VECT "component"
# define PARSE_ERR_NORM "vector has zero (or near-zero) norm"

#endif