/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 09:08:03 by thakala           #+#    #+#             */
/*   Updated: 2022/04/05 09:13:56 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* start drawing line from origin until the edge of the image */
int	draw_line(t_segm *s, t_prog *p, t_segm *o)
{
	t_db_pt	dt;
	t_db_pt	px;
	int		pxs;
	int		pt;

	if (s == NULL)
		return (RETURN_SUCCESS);
	swap_points(&s->b, &s->e, compare_heights(o->b, o->e, p->fdf));
	swap_points(&o->b, &o->e, compare_heights(o->b, o->e, p->fdf));
	dt = (t_db_pt){.row = s->e->row - s->b->row, .col = s->e->col - s->b->col};
// printf("dt: {.row == %f, .col == %f}\n", dt.row, dt.col);
	pxs = (int)sqrt(dt.row * dt.row + dt.col * dt.col);
	dt = (t_db_pt){.row = dt.row / pxs, .col = dt.col / pxs};
	px = (t_db_pt){.row = s->b->row, .col = s->b->col};
// printf("pxs: %d\n", pxs);
	pt = 0;
	while (pt <= pxs)
	{
// printf("px: {.row == %f, .col == %f}\n", px.row, px.col);
		if (in_range(0, (int)px.row, WIN_HEIGHT) \
			&& in_range(0, (int)px.col, WIN_WIDTH))
			my_mlx_pixel_put(&p->mlx->img, (int)px.col, (int)px.row, \
				get_colour((double)pt / pxs, o, p->fdf));
		px = (t_db_pt){.row = px.row + dt.row, \
			.col = px.col + dt.col};
		pt++;
	}
	return (RETURN_SUCCESS);
}

void	draw(t_mlx *mlx, t_fdf *fdf)
{
	t_pt	point;
	t_pt	p0;
	t_pt	p1;

	init_img(mlx, fdf);
	point.row = 0;
	while (point.row < fdf->map.line_count) // line_count one too many?
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
