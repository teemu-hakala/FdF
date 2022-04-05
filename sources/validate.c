/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 12:37:27 by thakala           #+#    #+#             */
/*   Updated: 2022/04/05 20:10:32 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	line_lengths_equal(t_fdf_map *map)
{
	if (map->line_count > 0 && map->lines[map->line_count - 1].point_count \
		!= map->lines[map->line_count].point_count)
	{
		exit_msg("Line lengths differ!\n", EXIT_ERROR);
	}
}
