/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 09:08:03 by thakala           #+#    #+#             */
/*   Updated: 2022/04/02 20:26:10 by thakala          ###   ########.fr       */
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

int	get_altitude(int altitude, t_fdf *fdf)
{
	return (altitude * fdf->zoom);
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

void	project(t_pt *dst, t_pt *src, t_fdf *fdf)
{
	int		screen_row;
	int		screen_col;
	int		ordinate;
	int		abscissa;
	int		altitude;

	ordinate = get_ordinate(src->row, fdf);
	abscissa = get_abscissa(src->col, fdf); // correct
	altitude = get_altitude(fdf->map.lines[src->row].line[src->col], fdf);
	screen_row = (int)((double)(-altitude) + (abscissa + ordinate) * sin(M_PI * 30 / 180));
	screen_col = (int)((double)(abscissa - ordinate) * cos(M_PI * 30 / 180));
	*dst = (t_pt){.row = screen_row, .col = screen_col};
}

int	in_range(int lowest, int value, int upto)
{
	return (lowest <= value && value < upto);
}

/* start drawing line from origin until the edge of the image */
int	draw_line(t_pt *p0, t_pt *p1, t_fdf *fdf, t_img *img)
{
	t_db_pt	dt;
	t_db_pt	px;
	int		px_count;

	(void) fdf;
	// if (compare_heights(p0, p1, fdf) == DO_SWAP)
	// 	swap_points(&p0, &p1);
	dt = (t_db_pt){.row = p1->row - p0->row, .col = p1->col - p0->col};
// printf("dt: {.row == %f, .col == %f}\n", dt.row, dt.col);
	px_count = (int)sqrt(dt.row * dt.row + dt.col * dt.col);
	dt = (t_db_pt){.row = dt.row / px_count, \
		.col = dt.col / px_count};
	px = (t_db_pt){.row = p0->row, .col = p0->col};
printf("px_count: %d\n", px_count);
	while (px_count--)
	{
printf("px: {.row == %f, .col == %f}\n", px.row, px.col);
		if (in_range(0, (int)px.row, WIN_HEIGHT) \
			&& in_range(0, (int)px.col, WIN_WIDTH))
			my_mlx_pixel_put(img, (int)px.col, (int)px.row, 0x00FFFFFF);
		px = (t_db_pt){.row = px.row + dt.row, \
			.col = px.col + dt.col};
	}
	return (RETURN_SUCCESS);
}

void	draw(t_mlx *mlx, t_fdf *fdf)
{
	t_pt	point;
	t_pt	p0;
	t_pt	p1;

	init_img(mlx);
	point.row = 0;
	while (point.row < fdf->map.line_count)
	{
		point.col = 0;
		while (point.col < fdf->map.lines[point.row].point_count)
		{
			project(&p0, &point, fdf);
			if (point.col + 1 < fdf->map.lines[point.row].point_count)
			{
				project(&p1, &(t_pt){.row = point.row, \
					.col = point.col + 1}, fdf);
				draw_line(&p0, &p1, fdf, &mlx->img);
			}
			if (point.row + 1 < fdf->map.line_count)
			{
				project(&p1, &(t_pt){.row = point.row + 1, \
					.col = point.col}, fdf);
				draw_line(&p0, &p1, fdf, &mlx->img);
			}
			point.col++;
		}
		point.row++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
	mlx_destroy_image(mlx->mlx, mlx->img.img);
}
