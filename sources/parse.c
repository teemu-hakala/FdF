/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 10:33:15 by thakala           #+#    #+#             */
/*   Updated: 2022/03/27 12:29:30 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	update_map_line_count(t_fdf_map *map, uint64_t current_line_count)
{
	int			**deletable_map;
	uint64_t	temp_line_count;

	if (map->line_count >= current_line_count)
		return ;
	deletable_map = map->map;
	temp_line_count = current_line_count * 3 / 2;
	map->map = (int **)malloc(sizeof(int *) * (temp_line_count + 1));
	if (map->map == NULL)
		exit_msg("map->map mallocation error!\n", EXIT_ERROR);
	ft_memcpy(map->map, deletable_map, map->line_count);
	map->line_count = temp_line_count;
	free(deletable_map);
}

static void	validate_line(char *line)
{
	uint64_t	i;
	int			invalidator_found;

	i = 0;
	invalidator_found = 0;
	while (line[i] && !invalidator_found)
	{
		if (line[i] == '-')
			i++;
		else
			invalidator_found = 1;
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

static void	add_line_to_map(t_fdf_map *map, char *line)
{
	ft_strsplit(line, ' ');
}

void	parse(char *filename, t_fdf_map *map)
{
	int			fd;
	char		*line;
	int			status;
	uint64_t	current_line_count;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_msg("File open error!\n", EXIT_ERROR);
	current_line_count = 0;
printf("map->line_count: %llu\n", map->line_count);
	while (1)
	{
		status = get_next_line(fd, &line);
		if (status < 0 || (status > 0 && line == NULL))
			exit_msg("get_next_line error", EXIT_ERROR);
		else if (status == 0)
			break ;
		current_line_count += (uint64_t)status;
		printf("%llu\n", current_line_count);
		update_map_line_count(map, current_line_count);
		validate_line(line);
		add_line_to_map(map, line);
		free(line);
printf("map->line_count: %llu\n", map->line_count);
	}
	//exit_msg("Parse error\n", EXIT_ERROR);
}
