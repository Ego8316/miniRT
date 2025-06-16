/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:46:12 by ego               #+#    #+#             */
/*   Updated: 2025/06/16 06:04:39 by ego              ###   ########.fr       */
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
 * given bool, prefixed by "minirt: ". If `status` is `false`, puts the
 * strings in red.
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
 * @param i The zero-based index in `line` to point the caret at.
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
	if (!ft_strchr(line, '\n'))
		printf("\n");
	i += ft_strlen(VERBOSE_PREFIX);
	while (--i >= 0)
		printf(" ");
	printf("^\n");
	printf("%s", C_RESET);
}

/**
 * @brief Prints a detailed parsing error message to standard error.
 * 
 * Displays a formatted error message indicating the location (line and column)
 * of a parsing error in the input file. Prefixes the message with
 * "miniRT: Error".
 * 
 * @param error The error message describing what went wrong.
 * @param line The line number where the error occured.
 * @param col The column number where the error occured.
 * 
 * @return Always returns `false` for convenience.
 */
bool	parse_errmsg(const char *error, t_parse_data *data)
{
	if (error)
	{
		errmsg("Error", 0, 0, false);
		if (data->verbose)
			print_error(data->line, data->i);
		ft_putstr_fd("File syntax error: ", STDERR_FILENO);
		ft_putstr_fd((char *)error, STDERR_FILENO);
		ft_putstr_fd(" at line ", STDERR_FILENO);
		ft_putnbr_fd(data->line_number + 1, STDERR_FILENO);
		ft_putstr_fd(", col ", STDERR_FILENO);
		ft_putnbr_fd(data->i + 1, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
	}
	return (false);
}
