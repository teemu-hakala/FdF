/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 10:33:15 by thakala           #+#    #+#             */
/*   Updated: 2022/03/27 14:14:29 by thakala          ###   ########.fr       */
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
	// map->map = (int **)malloc(sizeof(int *) * (temp_line_count + 1));
	map->lines = (t_line *)malloc(sizeof(t_line) * (temp_line_count + 1));
	if (map->lines == NULL)
		exit_msg("map->map mallocation error!\n", EXIT_ERROR);
	ft_memcpy(map->map, deletable_map, map->line_count * sizeof(t_line));
	map->line_count = temp_line_count;
	free(deletable_map);
}

static void	update_line_length(t_line *line, uint64_t current_point_count)
{
	int			*deletable_line;
	uint64_t	temp_point_count;

	if (line->len >= current_point_count)
		return ;
	deletable_line = line->line;
	temp_point_count = temp_point_count * 3 / 2;
	line->line = (int *)malloc(sizeof(int) * (temp_point_count));
	ft_memcpy(line->line, deletable_line, sizeof(int) * line->len);
	line->line = temp_point_count;
	free(deletable_line);
}

static void	add_line_to_map(t_fdf_map *map, char *line_string)
{
	char		**numerals;
	t_line		line;
	uint64_t	numeral;
	int			temp_height;

	numerals = ft_strsplit(line_string, ' ');
	line.len = 0;
	numeral = 0;
	while (numerals[numeral])
	{
		temp_height = ft_atoi(*numerals);
		update_line_length(&line, numeral);
		numeral++;
	}
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
