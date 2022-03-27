/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 10:33:15 by thakala           #+#    #+#             */
/*   Updated: 2022/03/27 10:45:15 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	**parse(char *filename, t_fdf *fdf)
{
	int		**map;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_msg("File open error!\n", EXIT_ERROR);
	(void) fdf;
	map = (int **)malloc(sizeof(int) * (INITIAL_LINE_COUNT + 1));
	exit_msg("Parse error\n", EXIT_ERROR);
	return (map);
}
