/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 10:33:15 by thakala           #+#    #+#             */
/*   Updated: 2022/03/27 11:09:49 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	update_map_line_count(t_map *map, uint64_t current_line_count)
{
	int		**deletable_map;

	if (map->line_count >= current_line_count)
		return ;
	deletable_map = map->map;
	map->map = (int **)malloc(sizeof(int) * (current_line_count + 1));
	ft_memcpy(map->map, deletable_map, map->line_count);
	map->line_count = current_line_count;
	free(deletable_map);
}

void	parse(char *filename, t_map *map)
{
	int			fd;
	uint64_t	current_line_count;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_msg("File open error!\n", EXIT_ERROR);
	current_line_count = 0;
	while (1)
	{
		update_map_line_count(map, current_line_count);
		break ;
	}
	exit_msg("Parse error\n", EXIT_ERROR);
}
