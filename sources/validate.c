/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 12:37:27 by thakala           #+#    #+#             */
/*   Updated: 2022/03/27 19:43:52 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Validates also file with minus sign at the end. */

void	validate_line(char *line)
{
	uint64_t	i;
	int			invalidator_found;

	i = 0;
	invalidator_found = 0;
	while (line[i] && !invalidator_found)
	{
		i += line[i] == '-';
		while (!invalidator_found)
		{
			if (!ft_isdigit(line[i]))
				invalidator_found = 1;
			i++;
		}
		if (line[i] == ' ')
			i++;
		else
			invalidator_found = 1;
		if (line[i] == '\0')
			invalidator_found = 0;
	}
	if (invalidator_found)
		exit_msg("Unknown character in map!\n", EXIT_ERROR);
}
