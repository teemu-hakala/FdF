/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 09:08:03 by thakala           #+#    #+#             */
/*   Updated: 2022/04/03 13:14:12 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int colour)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * data->bytes_per_pixel);
	*(unsigned int *)dst = (unsigned int)colour;
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

void	swap_points(t_pt **point0, t_pt **point1, int condition)
{
	t_pt	*temp;

	if (condition == DO_SWAP)
	{
		temp = *point0;
		*point0 = *point1;
		*point1 = temp;
	}
}

void	project(t_pt *dst, t_pt *src, t_fdf *fdf)
{
	int		screen_row;
	int		screen_col;
	int		ordinate;
	int		abscissa;
	int		altitude;

	ordinate = get_ordinate(src->row, fdf);
	abscissa = get_abscissa(src->col, fdf);
	altitude = get_altitude(fdf->map.lines[src->row].line[src->col], fdf);
	screen_row = (int)((double)(-altitude) \
		+ (abscissa + ordinate) * sin(M_PI * 30 / 180));
	screen_col = (int)((double)(abscissa - ordinate) *cos(M_PI * 30 / 180));
	*dst = (t_pt){.row = screen_row, .col = screen_col};
}

int	in_range(int lowest, int value, int upto)
{
	return (lowest <= value && value < upto);
}

double skew(double min, double percentage, double max)
{
	return (min + percentage * (1 - min) / max);
}

int	get_colour(double percentage, t_segm *pts, t_fdf *fdf)
{
	int		max_abs_height;
	double	height_percentage;
	int		colour_temp;

	max_abs_height = get_altitude(\
		abs_max(fdf->map.lines[pts->b->row].line[pts->b->col], \
				fdf->map.lines[pts->e->row].line[pts->e->col]), fdf);
	height_percentage = (double)max_abs_height / \
		get_altitude(fdf->map.max_height, fdf);
	if (fdf->map.lines[pts->b->row].line[pts->b->col] \
		!= fdf->map.lines[pts->e->row].line[pts->e->col])
		colour_temp = (int)(0xFF * \
			skew(LOWEST, percentage * height_percentage, HIGHEST)) << 16;
	else
		colour_temp = (int)(0xFF * height_percentage) << 16;
	if (colour_temp != 0)
		return (colour_temp);
	return ((int)(0xFF * LOWEST) << 16);
}

/* start drawing line from origin until the edge of the image */
int	draw_line(t_segm *s, t_prog *p, t_segm *o)
{
	t_db_pt	dt;
	t_db_pt	px;
	int		pxs;
	int		pt;

	swap_points(&s->b, &s->e, compare_heights(o->b, o->e, p->fdf));
	swap_points(&o->b, &o->e, compare_heights(o->b, o->e, p->fdf));
	dt = (t_db_pt){.row = s->e->row - s->b->row, .col = s->e->col - s->b->col};
// printf("dt: {.row == %f, .col == %f}\n", dt.row, dt.col);
	pxs = (int)sqrt(dt.row * dt.row + dt.col * dt.col);
	dt = (t_db_pt){.row = dt.row / pxs, .col = dt.col / pxs};
	px = (t_db_pt){.row = s->b->row, .col = s->b->col};
// printf("pxs: %d\n", pxs);
	pt = 0;
	while (pt++ < pxs)
	{
// printf("px: {.row == %f, .col == %f}\n", px.row, px.col);
		if (in_range(0, (int)px.row, WIN_HEIGHT) \
			&& in_range(0, (int)px.col, WIN_WIDTH))
			my_mlx_pixel_put(&p->mlx->img, (int)px.col, (int)px.row, \
				get_colour((double)pt / pxs, o, p->fdf));
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
				draw_line(&(t_segm){&p0, &p1}, &(t_prog){mlx, fdf, 0, 0}, \
					&(t_segm){&point, &(t_pt){.row = point.row, \
					.col = point.col + 1}});
			}
			if (point.row + 1 < fdf->map.line_count)
			{
				project(&p1, &(t_pt){.row = point.row + 1, \
					.col = point.col}, fdf);
				draw_line(&(t_segm){&p0, &p1}, &(t_prog){mlx, fdf, 0, 0}, \
					&(t_segm){&point, &(t_pt){.row = point.row + 1, \
					.col = point.col}});
			}
			point.col++;
		}
		point.row++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
	mlx_destroy_image(mlx->mlx, mlx->img.img);
}
