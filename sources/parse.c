/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 10:33:15 by thakala           #+#    #+#             */
/*   Updated: 2022/03/30 18:21:46 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Use ->size instead of ->len for the new size of malloc. */
static void	update_map_line_count(t_fdf_map *map)
{
	t_line		*deletable_lines;
	uint64_t	temp_size;

	if (map->size > map->line_count)
		return ;
	deletable_lines = map->lines;
	temp_size = map->line_count * 3 / 2 + !map->line_count;
	map->lines = (t_line *)malloc(sizeof(t_line) * (temp_size + 1));
	if (map->lines == NULL)
		exit_msg("map->lines mallocation error!\n", EXIT_ERROR);
	if (deletable_lines != NULL)
		ft_memcpy(map->lines, deletable_lines, map->size * sizeof(t_line));
	map->size = temp_size;
	free(deletable_lines);
}

/* Use ->size instead of ->len for the new size of malloc. */
static void	update_line_length(t_line *line, uint64_t current_point_count)
{
	int			*deletable_line;
	uint64_t	temp_size;

	if (line->size > current_point_count)
		return ;
	deletable_line = line->line;
// printf("%llu (current_point_count)\n", current_point_count);
	temp_size = current_point_count * 3 / 2 + !current_point_count;
// printf("%llu (temp_count)\n", temp_size);
	line->line = (int *)malloc(sizeof(int) * (temp_size + 1));
ft_bzero(line->line, sizeof(int) * (temp_size + 1));
	if (line->line == NULL)
		exit_msg("line->line mallocation error!\n", EXIT_ERROR);
	if (deletable_line != NULL)
// printf("%llu (line->size)\n", line->size);
		ft_memcpy(line->line, deletable_line, line->size * sizeof(int));
	line->size = temp_size;
	free(deletable_line);
}

static void	debug_print_line(t_line *line)
{
// printf("line->line in debug_print_line %p\n", line->line);
	for (uint64_t point = 0; point < line->point_count; point++)
	{
		printf("%d ", line->line[point]);
	}
	printf("\n");
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

/* line.point_count as numeral */

static void	add_line_to_map(t_fdf_map *map, char *line_string)
{
	char		**numerals;
	t_line		line;
	uint64_t	numeral;
	int			temp_height;

	ft_bzero(&line, sizeof(t_line));
	numerals = ft_strsplit(line_string, ' ');
	if (numerals == NULL)
		exit_msg("ft_strsplit return was NULL!\n", EXIT_ERROR);
	numeral = 0;
	while (numerals[numeral])
	{
		temp_height = ft_atoi(numerals[numeral]);
		if (numeral == 1)
		{
printf("temp_height:\n");
			ft_putnbr(temp_height);
		}
// printf("%d ", temp_height);
		update_line_length(&line, numeral);
// printf("line->line in add_line_to_map %p\n", line.line);
		line.line[numeral] = temp_height;
		numeral++;
	}
printf("line.line[i]: -->\n");
ft_putnbr(line.line[1]);
printf("\n");
	line.point_count = numeral;
printf("&line before assignment: \n");
	debug_print_line(&line);
	map->lines[map->line_count] = line;
//printf("map->lines[map->line_count]: %p\n", map->lines[map->line_count].line);
printf("&line after assignment: \n");
	debug_print_line(&line);
printf("&map->lines[map->line_count]: \n");
	debug_print_line(&map->lines[map->line_count]);
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
		validate_line(line);
		add_line_to_map(map, line);
		free(line);
		map->line_count += (uint64_t) !!status;
	}
	if (close(fd) < 0)
		exit_msg("file descriptor close(2) call error!\n", EXIT_ERROR);
	//exit_msg("Parse error\n", EXIT_ERROR);
}
