/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:19:42 by ego               #+#    #+#             */
/*   Updated: 2025/06/24 17:13:38 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

// Keys
# ifdef __linux__
#  define ESC 65307
# elif defined __APPLE__
#  define ESC 53
# endif
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
# define WORD_SIZE 15

// Attributes

# define REFLECTIVITY_ID "r"
# define BUMP_STRENGTH_ID "b"
# define MAX_ATTRIBUTES 2

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
# define SP_DIAMETER_MIN DBL_EPSILON
# define SP_DIAMETER_MAX 1000.0
# define CY_DIAMETER_MIN 0.1
# define CY_DIAMETER_MAX 500.0
# define CY_HEIGHT_MIN 0.001
# define CY_HEIGHT_MAX 1000.0
# define CO_ANGLE_MIN 0.1
# define CO_ANGLE_MAX 179.9
# define ATTR_MIN 0.0
# define ATTR_MAX 1.0
# define MAX_ARGS 3

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

# define PARSE_ERR_NO_IDENTIFIER_FOUND "no identifier found"
# define PARSE_ERR_UNKNOWN_IDENTIFIER "identifier does not match known types"
# define PARSE_ERR_UNKNOWN_ATTRIBUTE "unknown attribute"
# define PARSE_ERR_AMBIENT_DUPLICATE "duplicate ambient light definition"
# define PARSE_ERR_CAMERA_DUPLICATE "duplicate camera definition"
# define PARSE_ERR_REFLECTIVITY_DUPLICATE "reflectivity already defined"
# define PARSE_ERR_BUMP_STRENGTH_DUPLICATE "bump strength already defined"
# define PARSE_ERR_BOTH_MISSING "no camera nor ambient light definition"
# define PARSE_ERR_AMBIENT_MISSING "no ambient light definition"
# define PARSE_ERR_CAMERA_MISSING "no camera definition"

# define PARSE_ERR_UNEXPECTED_COMMA "unexpected comma"
# define PARSE_ERR_EXPECTED_COMMA "expected comma"
# define PARSE_ERR_EXPECTED_DOUBLE "expected double number"
# define PARSE_ERR_EXPECTED_INTEGER "expected integer number"
# define PARSE_ERR_UNEXPECTED_ARGUMENT "unexpected argument"

# define PARSE_ERR_TOO_FEW_ARGUMENTS "not enough data fields after identifier"
# define PARSE_ERR_TOO_MANY_ARGUMENTS "more than expected data fields"
# define PARSE_ERR_EXTRA_DATA "unexpected trailing data after valid fields"

# define PARSE_ERR_INVALID_COLOR "invalid color, expected `checkerboard'"
# define PARSE_ERR_NORM "vector has zero (or near-zero) norm"
# define PARSE_ERR_BOUND "out of range"
# define PARSE_ERR_BOUND_COLOR "color value"
# define PARSE_ERR_BOUND_COORD "coordinate"
# define PARSE_ERR_BOUND_BRIGHTNESS "brightness value"
# define PARSE_ERR_BOUND_FOV "fov value"
# define PARSE_ERR_BOUND_DIAMETER "diameter"
# define PARSE_ERR_BOUND_HEIGHT "height"
# define PARSE_ERR_BOUND_ANGLE "angle"
# define PARSE_ERR_BOUND_REFLECTIVITY "reflectivity"
# define PARSE_ERR_BOUND_BUMP_STRENGTH "bump strength"
# define PARSE_ERR_BOUND_VECT "component"

#endif
