/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 19:21:27 by ego               #+#    #+#             */
/*   Updated: 2025/06/16 18:10:56 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	return ;
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
 * @brief Adds a new light to the end of a linked list of lights. If the list
 * is empty, the new light becomes the head.
 * 
 * @param new New light to add.
 * @param lights Pointer to the head of the lights list.
 */
void	add_light_to_list(t_light *new, t_light **lights)
{
	t_light	*l;

	if (!*lights)
	{
		*lights = new;
		return ;
	}
	l = *lights;
	while (l->next)
		l = l->next;
	l->next = new;
	return ;
}

/**
 * @brief Adds a new object to the end of a linked list of objects. If the list
 * is empty, the new object becomes the head.
 * 
 * @param new New object to add.
 * @param objects Pointer to the head of the objects list.
 */
void	add_object_to_list(t_object *new, t_object **objects)
{
	t_object	*o;

	if (!*objects)
	{
		*objects = new;
		return ;
	}
	o = *objects;
	while (o->next)
		o = o ->next;
	o->next = new;
	return ;
}
