/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 10:33:15 by thakala           #+#    #+#             */
/*   Updated: 2022/04/04 20:56:01 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	update_map_line_count(t_fdf_map *map)
{
	t_row		*del_lines;
	int			temp_size;

	if (map->size > map->line_count)
		return ;
	del_lines = map->lines;
	temp_size = map->line_count * 3 / 2 + 1;
	if (temp_size < 0)
		exit_msg("temp_size < 0\n", EXIT_ERROR);
	map->lines = (t_row *)malloc(sizeof(t_row) * (((size_t)temp_size) + 1));
	if (map->lines == NULL)
		exit_msg("map->lines mallocation error!\n", EXIT_ERROR);
	if (del_lines != NULL)
		ft_memcpy(map->lines, del_lines, (size_t)map->size * sizeof(t_row));
	map->size = temp_size;
	free(del_lines);
}

static void	update_line_length(t_row *line)
{
	int			*deletable_line;
	int			temp_size;

	if (line->size > line->point_count)
		return ;
	deletable_line = line->line;
	temp_size = line->point_count * 3 / 2 + 1;
	if (temp_size < 0)
		exit_msg("temp_size < 0\n", EXIT_ERROR);
	line->line = (int *)malloc(sizeof(int) * (size_t)temp_size); // removed + 1
	if (line->line == NULL)
		exit_msg("line->line mallocation error!\n", EXIT_ERROR);
	if (deletable_line != NULL)
		ft_memcpy(line->line, deletable_line, (size_t)line->size * sizeof(int));
	line->size = temp_size;
	free(deletable_line);
}

static void	*free_splits(char **strings)
{
	char	**string_splits;
	char	*temp_string;

	string_splits = strings;
	while (*strings)
	{
		temp_string = *strings++;
		free(temp_string);
	}
	free(string_splits);
	return (NULL);
}

static void	add_line_to_map(t_fdf_map *map, char *line_string)
{
	char		**numerals;
	t_row		line;
	int			temp_height;

	ft_bzero(&line, sizeof(t_row));
	numerals = ft_strsplit(line_string, ' ');
	if (numerals == NULL)
		exit_msg("ft_strsplit return was NULL!\n", EXIT_ERROR);
	while (numerals[line.point_count])
	{
		temp_height = ft_atoi(numerals[line.point_count]);
		update_line_length(&line);
		if (temp_height > map->height.max)
			map->height.max = temp_height;
		if (temp_height < map->height.min)
			map->height.min = temp_height;
		line.line[line.point_count++] = temp_height;
	}
	if (map->max_point_count < line.point_count)
		map->max_point_count = line.point_count;
	map->lines[map->line_count] = line;
	numerals = free_splits(numerals);
}

void	parse(char *filename, t_fdf_map *map)
{
	int			fd;
	char		*line;
	int			status;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_msg("File open error!\n", EXIT_ERROR);
	while (1)
	{
		status = get_next_line(fd, &line);
		if (status < 0 || (status > 0 && line == NULL))
			exit_msg("get_next_line error", EXIT_ERROR);
		else if (status == 0)
			break ;
		update_map_line_count(map);
		//validate_line(line);
		add_line_to_map(map, line);
		free(line);
		line_lengths_equal(map);
		map->line_count += (uint64_t) !!status;
	}
	free(line); //Double free? Does gnl place NULL in *line when returns 0?
	if (close(fd) < 0)
		exit_msg("file descriptor close(2) call error!\n", EXIT_ERROR);
}
