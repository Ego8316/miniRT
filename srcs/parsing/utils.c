/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 19:21:27 by ego               #+#    #+#             */
/*   Updated: 2025/06/19 02:09:44 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Gets the next word and stores it inside the given buffer. Skips any
 * leading whitespace and attempts to copy the next sequence of alphabetic
 * character. The position of the word's start is stored in `word_start` for
 * error reporting purposes.
 * 
 * @param data Parsing data.
 * @param word Buffer to store the word.
 * @param word_start Start index of the next word.
 * 
 * @return `true` if a word was found, `false` otherwise.
 * 
 * @warning The word buffer must be at least `WORD_SIZE` bytes.
 */
bool	get_next_word(t_parse_data *data, char *word, int *word_start)
{
	int	i;

	skip_spaces(data);
	*word_start = data->i;
	if (!data->line[data->i] || !ft_isalpha(data->line[data->i]))
		return (false);
	i = 0;
	while (ft_isalpha(data->line[data->i]) && i < WORD_SIZE)
	{
		word[i++] = data->line[data->i++];
	}
	word[i] = 0;
	return (true);
}

/**
 * @brief Advances the parsing index past all whitespace characters.
 * 
 * @param data Parsing data.
 */
void	skip_spaces(t_parse_data *data)
{
	while (ft_isspace(data->line[data->i]))
		++data->i;
	return ;
}

/**
 * @brief Checks for unexpected trailing data after parsing expected fields.
 * If found, prints the appropriate error message.
 * 
 * @param data Parsing data.
 * 
 * @return `true` if unexpected trailing data exists, `false` otherwise.
 */
bool	trailing_data(t_parse_data *data)
{
	skip_spaces(data);
	if (data->line[data->i])
		return (!parse_errmsg(PARSE_ERR_EXTRA_DATA, data, true, false));
	return (false);
}

/**
 * @brief Parses and assigns an object attribute. Searches for the provided
 * word `word` in the array of known attributes `a` and ensures this attribute
 * has not already been set, then parses its value into the target memory
 * location.
 * 
 * @param d Parsing data.
 * @param a Array of attribute descriptors.
 * @param i Position in the line where the attribute was found.
 * @param word The attribute name to find and parse.
 * 
 * @return `true` if the attribute was successfully parsed and set, `false`
 * otherwise.
 */
bool	get_attribute(t_parse_data *d, t_attribute *a, int i, const char *word)
{
	int	j;

	j = -1;
	while (++j < MAX_ATTRIBUTES)
	{
		if (!ft_strcmp(word, a[j].id))
		{
			if (a[j].found)
			{
				d->i = i;
				return (parse_errmsg(a[j].dup_err, d, true, false));
			}
			a[j].found = true;
			d->boundaries = a[j].bound;
			if (!get_next_double(d, a[j].value, false, true))
				return (false);
			return (true);
		}
	}
	d->i = i;
	return (parse_errmsg(PARSE_ERR_UNKNOWN_ATTRIBUTE, d, true, false));
}
