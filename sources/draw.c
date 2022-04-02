/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 09:08:03 by thakala           #+#    #+#             */
/*   Updated: 2022/04/02 09:22:17 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
	<placeholder for a definitive comment>
*/

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * data->bytes_per_pixel);
	*(unsigned int *)dst = (unsigned int)color;
}

void	init_img(t_mlx *mlx)
{
	mlx->img.img = mlx_new_image(mlx->mlx, WIN_WIDTH, WIN_HEIGHT);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img.bits_per_pixel, \
		&mlx->img.line_length, &mlx->img.endian);
	mlx->img.bytes_per_pixel = mlx->img.bits_per_pixel / 8;
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

int	compare_heights(t_pt *point0, t_pt *point1, t_fdf *fdf)
{
	if (fdf->map.lines[point0->row].line[point0->col] \
		> fdf->map.lines[point1->row].line[point1->col])
	{
		return (DO_SWAP);
	}
	return (NO_SWAP);
}

void	swap_points(t_pt **point0, t_pt **point1)
{
	t_pt	*temp;

	temp = *point0;
	*point0 = *point1;
	*point1 = temp;
}

double	project(double scalar)
{
	return (scalar);
}

int	in_range(int lowest, int value, int upto)
{
	return (lowest <= value && value < upto);
}

/* start drawing line from origin until the edge of the image */
int	draw_debug_line(t_pt *point0, t_pt *point1, t_fdf *fdf, t_img *image)
{
	t_db_pt	delta;
	t_db_pt	pixel;
	int		pixel_count;

	(void) fdf;
	delta = (t_db_pt){.row = point1->row - point0->row, \
		.col = point1->col - point0->col};
printf("delta: {.row == %f, .col == %f}\n", delta.row, delta.col);
	pixel_count = (int)sqrt(delta.row * delta.row + delta.col * delta.col);
	delta = (t_db_pt){.row = delta.row / pixel_count, \
		.col = delta.col / pixel_count};
	pixel = (t_db_pt){.row = point0->row, \
		.col = point0->col};
printf("pixel_count: %d\n", pixel_count);
	while (pixel_count--)
	{
printf("pixel: {.row == %f, .col == %f}\n", pixel.row, pixel.col);
		if (in_range(0, (int)pixel.row, WIN_HEIGHT) \
			&& in_range(0, (int)pixel.col, WIN_WIDTH))
			my_mlx_pixel_put(image, (int)pixel.col, \
				(int)pixel.row, 0x00FFFFFF);
		pixel = (t_db_pt){.row = pixel.row + delta.row, \
			.col = pixel.col + delta.col};
	}
	return (RETURN_SUCCESS);
}

/* start drawing line from origin until the edge of the image */
int	draw_line(t_pt *point0, t_pt *point1, t_fdf *fdf, t_img *image)
{
	t_db_pt	delta;
	t_db_pt	pixel;
	t_db_pt	projected_pixel;
	int		pixel_count;

	if (compare_heights(point0, point1, fdf) == DO_SWAP)
		swap_points(&point0, &point1);
	delta = (t_db_pt){.row = get_ordinate(point1->row, fdf) - \
		get_ordinate(point0->row, fdf), .col = get_abscissa(point1->col, fdf) \
		- get_abscissa(point0->col, fdf)};
// printf("delta: {.row == %f, .col == %f}\n", delta.row, delta.col);
	pixel_count = (int)sqrt(delta.row * delta.row + delta.col * delta.col);
	delta = (t_db_pt){.row = delta.row / pixel_count, \
		.col = delta.col / pixel_count};
	pixel = (t_db_pt){.row = get_ordinate(point0->row, fdf), \
		.col = get_abscissa(point0->col, fdf)};
// printf("pixel_count: %d\n", pixel_count);
	while (pixel_count--)
	{
// printf("pixel: {.row == %f, .col == %f}\n", pixel.row, pixel.col);
		projected_pixel = (t_db_pt){.row = project(pixel.row), \
			.col = project(pixel.col)};
		if (in_range(0, (int)projected_pixel.row, WIN_HEIGHT) \
			&& in_range(0, (int)projected_pixel.col, WIN_WIDTH))
			my_mlx_pixel_put(image, (int)projected_pixel.col, \
				(int)projected_pixel.row, 0x00FFFFFF);
		pixel = (t_db_pt){.row = pixel.row + delta.row, \
			.col = pixel.col + delta.col};
	}
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
