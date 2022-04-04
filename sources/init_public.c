/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_public.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 20:44:21 by thakala           #+#    #+#             */
/*   Updated: 2022/04/04 22:52:06 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_origin(t_fdf *fdf)
{
	fdf->origin = (t_pt){.row = get_ordinate(fdf->map.line_count, fdf) / 2, \
		.col = get_abscissa(fdf->map.max_point_count, fdf) / 2};
}

void	reset_origin(t_fdf *fdf)
{
printf("fdf->prigin.row: %d, fdf->prigin.col: %d\n", fdf->origin.row, fdf->origin.col);
	fdf->origin = (t_pt){.row = (fdf->map.line_count - 1) * fdf->zoom / 2, \
		.col = fdf->map.max_point_count * fdf->zoom / 2};
	fdf->offset = (t_pt){.row = WIN_HEIGHT / 2 - fdf->origin.row, \
		.col = WIN_WIDTH / 2 - fdf->origin.col};
printf("fdf->origin.row: %d, fdf->origin.col: %d\n", fdf->origin.row, fdf->origin.col);
}

void	init_offset(t_fdf *fdf)
{
	fdf->offset = (t_pt){.row = WIN_HEIGHT / 2 - fdf->origin.row, \
		.col = WIN_WIDTH / 2 - fdf->origin.col};
}

void	init_map(t_fdf_map *map)
{
	map->height.max = INT_MIN;
	map->height.min = INT_MAX;
}
