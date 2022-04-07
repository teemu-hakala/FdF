/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 09:08:03 by thakala           #+#    #+#             */
/*   Updated: 2022/04/07 09:55:16 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	draw_line(t_segm *s, t_prog *p, t_segm *o)
{
	t_db_pt	dt;
	t_db_pt	px;
	int		pxs;
	int		pt;
	int		swap;

	swap = compare_heights(o->b, o->e, p->fdf);
	dt = (t_db_pt){.row = s->e->row - s->b->row, .col = s->e->col - s->b->col};
	pxs = (int)sqrt(dt.row * dt.row + dt.col * dt.col);
	if (pxs == 0)
		return (RETURN_SUCCESS);
	dt = (t_db_pt){.row = dt.row / pxs, .col = dt.col / pxs};
	px = (t_db_pt){.row = s->b->row, .col = s->b->col};
	pt = 0;
	while (pt <= pxs)
	{
		if (in_range(0, (int)px.row, WIN_HEIGHT) \
			&& in_range(0, (int)px.col, WIN_WIDTH))
		{
			if (swap)
				my_mlx_pixel_put(&p->mlx->img, (int)px.col, (int)px.row, \
					get_colour((double)1.0 - (double)pt / pxs, o, p->fdf));
			else
				my_mlx_pixel_put(&p->mlx->img, (int)px.col, (int)px.row, \
					get_colour((double)pt / pxs, o, p->fdf));
		}
		else
			break ;
		px = (t_db_pt){.row = px.row + dt.row, .col = px.col + dt.col};
		pt++;
	}
	return (RETURN_SUCCESS);
}

/*void	segment_feeder(t_mlx *mlx, t_fdf *fdf, t_pt *point)
{
	t_pt	p0;
	t_pt	p1;

	project(&p0, point, fdf);
	if (point->col + 1 < fdf->map.lines[point->row].point_count)
	{
		project(&p1, &(t_pt){.row = point->row, \
			.col = point->col + 1}, fdf);
		draw_line(&(t_segm){&p0, &p1}, &(t_prog){mlx, fdf, 0, 0}, \
			&(t_segm){point, &(t_pt){.row = point->row, \
			.col = point->col + 1}});
	}
	if (point->row + 1 < fdf->map.line_count)
	{
		project(&p1, &(t_pt){.row = point->row + 1, \
			.col = point->col}, fdf);
		draw_line(&(t_segm){&p0, &p1}, &(t_prog){mlx, fdf, 0, 0}, \
			&(t_segm){point, &(t_pt){.row = point->row + 1, \
			.col = point->col}});
	}
}*/

void	draw(t_mlx *mlx, t_fdf *fdf)
{
	t_pt	point;

	init_img(mlx, fdf);
	point.row = 0;
	while (point.row < fdf->map.line_count)
	{
		point.col = 0;
		while (point.col < fdf->map.lines[point.row].point_count)
		{
			segment_feeder(mlx, fdf, &point);
			point.col++;
		}
		point.row++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
	mlx_destroy_image(mlx->mlx, mlx->img.img);
}
