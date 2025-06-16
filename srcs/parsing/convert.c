/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 01:55:34 by ego               #+#    #+#             */
/*   Updated: 2025/06/16 05:50:13 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Helper function for `ft_strtod` to parse the fractional part of a
 * floating-point number starting just after the decimal point.
 * 
 * @param str Pointer to the decimal point character '.' in the input string.
 * @param value Pointer to the current double value to accumulate fractional
 * digits.
 * 
 * @return Pointer to the first character in the input string after the last
 * digit of the fractional part.
 */
static const char	*get_fractional_value(const char *str, double *value)
{
	double	fraction;

	fraction = 0.1;
	str++;
	while (ft_isdigit(*str))
	{
		*value += (*str - '0') * fraction;
		fraction *= 0.1;
		str++;
	}
	return (str);
}

/**
 * @brief Parses the `str` string interpreting its content as a floating point
 * number and returns its value as a `double`. If `endptr` is not a null
 * pointer, also sets its value to point to the first character after the
 * number.
 * 
 * @param str String beginning with the representation of a floating point
 * number.
 * @param endptr Reference to an already allocated string whose value is set
 * to the next character in `str` after the numerical value. If NULL, not used.
 * 
 * @return On success, returns the converted number, 0 otherwise.
 */
double	ft_strtod(const char *str, char **endptr)
{
	double	result;
	int		sign;

	result = 0.0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		result = result * 10.0 + (*str - '0');
		str++;
	}
	if (*str == '.')
		str = get_fractional_value(str, &result);
	if (endptr)
		*endptr = (char *)str;
	return (sign * result);
}

/**
 * @brief Helper function for ft_strtol to parse the digits of an integer number
 * in a specified base and accumulate the result.
 * 
 * @param str Pointer to the first digit character in the input string.
 * @param base Numerical base (e.g., 10 for decimal, 16 for hex).
 * @param value Pointer to a long integer where the parsed value will be
 * accumulated.
 * 
 * @return Pointer to the first character in the input string after the last
 * valid digit.
 */
static const char	*get_value(const char *str, int base, long *value)
{
	int	digit;

	digit = 0;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			digit = *str - '0';
		else if (*str >= 'A' && *str <= 'Z')
			digit = *str - 'A' + 10;
		else if (*str >= 'a' && *str <= 'z')
			digit = *str - 'a' + 10;
		else
			break ;
		if (digit >= base)
			break ;
		*value = *value * base + digit;
		str++;
	}
	return (str);
}

/**
 * @brief Parses the `str` string interpreting its content as an integral
 * number of the specified `base` and returns its value as a `long`. If
 * `endptr` is not a null pointer, also sets its value to point to the
 * first character after the number.
 * 
 * @param str String beginning with the representation of an integral number.
 * @param endptr Pointer to a string whose value is set to the next character
 * in `str` after the numerical value. If NULL, not used.
 * @param base Numerical base that determines the valid characters and their
 * interpretation.
 * 
 * @return On success, returns the converted number, 0 otherwise.
 */
long	ft_strtol(const char *str, char **endptr, int base)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	if (base < 2 || base > 36)
	{
		if (endptr)
			*endptr = (char *)str;
		return (0);
	}
	while (ft_isspace(*str))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		sign = -1;
		str++;
	}
	str = get_value(str, base, &result);
	if (endptr)
		*endptr = (char *)str;
	return (sign * result);
}
