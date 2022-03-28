/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 10:33:15 by thakala           #+#    #+#             */
/*   Updated: 2022/03/28 19:29:00 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Use ->size instead of ->len for the new size of malloc. */
static void	update_map_line_count(t_fdf_map *map, uint64_t current_line_count)
{
	t_line		*deletable_lines;
	uint64_t	temp_size;

	if (map->size >= current_line_count)
		return ;
	deletable_lines = map->lines;
	temp_size = current_line_count * 3 / 2;
	map->lines = (t_line *)malloc(sizeof(t_line) * (temp_size + 1));
	if (map->lines == NULL)
		exit_msg("map->lines mallocation error!\n", EXIT_ERROR);
	ft_memcpy(map->lines, deletable_lines, map->size * sizeof(t_line));
	map->size = temp_size;
	free(deletable_lines);
}

/* Use ->size instead of ->len for the new size of malloc. */
static void	update_line_length(t_line *line, uint64_t current_point_count)
{
	int			*deletable_line;
	uint64_t	temp_size;

	if (line->size >= current_point_count)
		return ;
	deletable_line = line->line;
	temp_size = current_point_count * 3 / 2;
	line->line = (int *)malloc(sizeof(int) * (temp_size + 1));
	if (line->line == NULL)
		exit_msg("line->line mallocation error!\n", EXIT_ERROR);
	ft_memcpy(line->line, deletable_line, line->size * sizeof(int));
	line->size = temp_size;
	free(deletable_line);
}

static void	add_line_to_map(t_fdf_map *map, char *line_string)
{
	char		**numerals;
	t_line		line;
	uint64_t	numeral;
	int			temp_height;

	numerals = ft_strsplit(line_string, ' ');
	line.point_count = 0;
	numeral = 0;
	while (numerals[numeral])
	{
		temp_height = ft_atoi(*numerals);
		update_line_length(&line, numeral);
		numeral++;
	}
	map->lines[map->line_count] = line;
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
printf("map->line_count: %llu\n", map->line_count++);
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
