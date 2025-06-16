/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:38:37 by ego               #+#    #+#             */
/*   Updated: 2025/06/16 13:37:43 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Prints the current state of the parsing data.
 * 
 * Displays current line number and content, parsing progress, identifier and
 * parsing flags.
 * 
 * @param data Current parsing data.
 */
void	print_parse_data(t_parse_data *data)
{
	int	i;

	printf("\n-------------------  PARSE DATA  -------------------\n");
	printf("Line [%i]:\t\t%s%s%s",
		data->line_number, COLOR_B, data->line, C_RESET);
	if (!ft_strchr(data->line, '\n'))
		printf("\n");
	printf("Index position:\t\t");
	i = 0;
	while (++i < data->i)
		printf(" ");
	printf("%s^%s\n", COLOR_R, C_RESET);
	printf("Current index:\t\t%i\n", data->i);
	printf("Current identifier:\t%s\n", get_id_string(data->id));
	printf("Ambient found:\t\t%i\n", data->ambient_found);
	printf("Camera found:\t\t%i\n", data->camera_found);
	printf("Field count:\t\t%i\n", data->field_count);
	printf("-----------------------------------------------------\n");
}
