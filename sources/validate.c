/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 12:37:27 by thakala           #+#    #+#             */
/*   Updated: 2022/03/29 19:16:47 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Validates also file with minus sign at the end.
	When ft_atoi returns 0, check if the digit is actually zero. */

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
			i += !invalidator_found;
		}
		while (line[i] == ' ')
			i++;
		if (ft_isdigit(line[i]) || line[i] == '\0')
			invalidator_found = 0;
	}
	if (invalidator_found)
		exit_msg("Unknown character in map!\n", EXIT_ERROR);
}
