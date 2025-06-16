/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 19:21:27 by ego               #+#    #+#             */
/*   Updated: 2025/06/16 06:05:49 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Initializes the parse data structure for file parsing.
 * 
 * Sets up all global fields of the given data structure to their initial
 * values before parsing the file.
 * 
 * @param Pointer to the parse data structure being initialized.
 */
void	init_parse_global_data(t_parse_data *data)
{
	data->ambient_found = false;
	data->camera_found = false;
	data->line_number = -1;
	data->verbose = true;
	return ;
}

/**
 * @brief Initalizes a parse data structure for line parsing.
 * 
 * Sets up all line fields of the given data structure to their initial values
 * before parsing a new line from the scene file.
 * 
 * @param data Pointer to the parse data structure being initialized.
 */
void	init_parse_line_data(t_parse_data *data)
{
	data->i = 0;
	data->id = NONE;
	data->field_count = 0;
	return ;
}

void	skip_spaces(t_parse_data *data)
{
	while (ft_isspace(data->line[data->i]))
		++data->i;
	return ;
}

/**
 * @brief Checks if a string is only made of one given type.
 * 
 * @param s String to be checked.
 * @param f Function used to check the type (isspace for example).
 * 
 * @return `true` if it is only made of the given type, `false` otherwise.
 */
bool	stristype(const char *s, bool (*f)(int))
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!f(s[i]))
			return (false);
		i++;
	}
	return (true);
}

/** 
 * @brief Checks if a character is a space.
 * 
 * @param c The character to check.
 * 
 * @return 1 if the character is a space, 0 otherwise.
 */
bool	ft_isspace(int c)
{
	return ((9 <= c && c <= 13) || c == 32);
}
