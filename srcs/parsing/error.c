/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:46:12 by ego               #+#    #+#             */
/*   Updated: 2025/06/17 00:53:37 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Prints the string prefix corresponding to a given identifier.
 * 
 * @param id Identifier.
 */
static void	print_id_prefix(t_id id)
{
	if (id == SPHERE)
		ft_putstr_fd("sphere: ", STDERR_FILENO);
	else if (id == PLANE)
		ft_putstr_fd("plane: ", STDERR_FILENO);
	else if (id == CYLINDER)
		ft_putstr_fd("cylinder: ", STDERR_FILENO);
	else if (id == CONE)
		ft_putstr_fd("cone: ", STDERR_FILENO);
	else if (id == PARABOLOID)
		ft_putstr_fd("paraboloid: ", STDERR_FILENO);
	else if (id == HYPERBOLOID)
		ft_putstr_fd("hyperboloid: ", STDERR_FILENO);
	else if (id == AMBIENT)
		ft_putstr_fd("ambient: ", STDERR_FILENO);
	else if (id == CAMERA)
		ft_putstr_fd("camera: ", STDERR_FILENO);
	else if (id == LIGHT)
		ft_putstr_fd("light: ", STDERR_FILENO);
	else
		ft_putstr_fd("unknown id: ", STDERR_FILENO);
}

/**
 * @brief Prints on the standard error up to three strings and returns the
 * given bool, prefixed by "minirt: ". If `status` is `false`, puts the
 * strings in red.
 * 
 * @param s1 First string to be printed (can be `NULL`).
 * @param s2 Second string to be printed (can be `NULL`).
 * @param s3 Third string to be printed (can be `NULL`).
 * @param status Status to return.
 * 
 * @return The input `status` value.
 */
bool	errmsg(char *s1, char *s2, char *s3, bool status)
{
	if (s1 || s2 || s3)
		ft_putstr_fd(PREFIX, STDERR_FILENO);
	if (!status)
		ft_putstr_fd(COLOR_R, STDERR_FILENO);
	if (s1)
		ft_putstr_fd(s1, STDERR_FILENO);
	if (s2)
		ft_putstr_fd(s2, STDERR_FILENO);
	if (s3)
		ft_putstr_fd(s3, STDERR_FILENO);
	if (!status)
		ft_putstr_fd(C_RESET, STDERR_FILENO);
	if (s1 || s2 || s3)
		ft_putchar_fd('\n', STDERR_FILENO);
	return (status);
}

/**
 * @brief Prints the given line with a caret pointing at the specified index.
 * 
 * Outputs the line prefixed with "line : " in a colored format, followed by
 * a newline (if not already present). Then prints spaces or tabs up to the
 * given index (adjusted by the prefix length), and finally prints a caret '^'
 * underneath to visually indicate the error position.
 * 
 * @param line The input line string where the error occurred.
 * @param i Zero-based index in `line` to point the caret at.
 */
static void	print_error(char *line, int i)
{
	int	j;

	printf("%s", VERBOSE_PREFIX);
	printf("%s", COLOR_O);
	j = 0;
	while (line[j])
	{
		if (ft_isspace(line[j]))
			printf(" ");
		else
			printf("%c", line[j]);
		j++;
	}
	printf("\n");
	i += ft_strlen(VERBOSE_PREFIX);
	while (--i >= 0)
		printf(" ");
	printf("^%s\n", C_RESET);
}

/**
 * @brief Prints detailed boundary error information to standard error.
 * 
 * Displays the error message describing a boundary violation, including the
 * allowed minimum and maximum values.
 * 
 * @param data Parsing data.
 */
static void	print_bound_error(t_parse_data *data)
{
	ft_putstr_fd((char *)data->boundaries.err, STDERR_FILENO);
	ft_putchar_fd(' ', STDERR_FILENO);
	ft_putstr_fd((char *)PARSE_ERR_BOUND, STDERR_FILENO);
	ft_putstr_fd(" (", STDERR_FILENO);
	ft_putdouble_fd(data->boundaries.min, 1, STDERR_FILENO);
	ft_putstr_fd(" to ", STDERR_FILENO);
	ft_putdouble_fd(data->boundaries.max, 1, STDERR_FILENO);
	ft_putstr_fd(") ", STDERR_FILENO);
}

/**
 * @brief Prints a detailed parsing error message to standard error.
 * 
 * Displays a formatted error message indicating the location (line and column)
 * of a parsing error in the input file. Prefixes the message with
 * "miniRT: Error". Optionally prints detailed boundary violation info.
 * 
 * @param err Error message describing what went wrong.
 * @param d Parsing data.
 * @param verb Enable prefix in the error.
 * @param bound If true, print boundary violation details.
 * 
 * @return Always returns `false` for convenience in error handling.
 */
bool	parse_errmsg(const char *err, t_parse_data *d, bool verb, bool bound)
{
	if (verb)
	{
		errmsg("Error", 0, 0, false);
		if (d)
			print_error(d->line, d->i);
		ft_putstr_fd("File syntax error: ", STDERR_FILENO);
		if (d && d->verbose)
			print_id_prefix(d->id);
		if (bound)
			print_bound_error(d);
		else
			ft_putstr_fd((char *)err, STDERR_FILENO);
		if (d)
		{
			ft_putstr_fd(" at line ", STDERR_FILENO);
			ft_putnbr_fd(d->line_number + 1, STDERR_FILENO);
			ft_putstr_fd(", col ", STDERR_FILENO);
			ft_putnbr_fd(d->i + 1, STDERR_FILENO);
		}
		ft_putchar_fd('\n', STDERR_FILENO);
	}
	return (false);
}
