/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 09:08:03 by thakala           #+#    #+#             */
/*   Updated: 2022/03/31 09:40:40 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
	<placeholder for a definitive comment>
*/

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = (unsigned int)color;
}

void	init_img(t_mlx *mlx)
{
	mlx->img.img = mlx_new_image(mlx->mlx, WIN_WIDTH, WIN_HEIGHT);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img.bits_per_pixel, \
		&mlx->img.line_length, &mlx->img.endian);
}

/* void	debug_printer(t_fdf_map *map)
{
	for (uint64_t line = 0; line < map->line_count; line++)
	{
		for (uint64_t point = 0; point < map->lines[line].point_count; point++)
		{
			printf("%d ", map->lines[line].line[point]);
		}
		printf("\n");
	}
	printf("\n");
} */

int	get_ordinate(int ordinate, t_fdf *fdf)
{
	return (ordinate * fdf->zoom + fdf->offset.row);
}

int	get_abscissa(int abscissa, t_fdf *fdf)
{
	return (abscissa * fdf->zoom + fdf->offset.col);
}

/* start drawing line from origin until the edge of the image */
int	draw_line(t_pt *point0, t_pt *point1, t_fdf *fdf, t_img *image)
{
	my_mlx_pixel_put(image, get_ordinate(point0->row, fdf), \
		get_abscissa(point0->col, fdf), 0x00FFFFFF);
	//fdf->map.lines[point->row].line[point->col];
	return (RETURN_SUCCESS);
}

void	draw(t_mlx *mlx, t_fdf *fdf)
{
	t_pt	point;

	// debug_printer(&fdf->map);
	init_img(mlx);
	point.row = 0;
	while (point.row < fdf->map.line_count)
	{
		point.col = 0;
		while (point.col < fdf->map.lines[point.row].point_count)
		{
			if (point.col + 1 < fdf->map.lines[point.row].point_count)
				draw_line(&point, &(t_pt){.row = point.row, \
					.col = point.col + 1}, fdf, &mlx->img);
			if (point.row + 1 < fdf->map.line_count)
				draw_line(&point, &(t_pt){.row = point.row + 1, \
					.col = point.col}, fdf, &mlx->img);
			point.col++;
		}
		point.row++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
	mlx_destroy_image(mlx->mlx, mlx->img.img);
}
