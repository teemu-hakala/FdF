/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 09:08:03 by thakala           #+#    #+#             */
/*   Updated: 2022/04/03 19:00:41 by thakala          ###   ########.fr       */
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

int	overlaps_1d(t_mmd *iv0, t_mmd *iv1)
{
	return (iv0->max >= iv1->min && iv1->max >= iv0->min);
}

int	overlaps_2d(t_rect *r0, t_rect *r1)
{
	return (overlaps_1d(&r0->rows, &r1->rows) \
		&& overlaps_1d(&r0->cols, &r1->cols));
}

t_rect	*rectangularize(t_mmd *rows, t_mmd *cols, t_rect *result)
{
	result->rows = (t_mmd){.min = rows->min, .max = rows->max};
	result->cols = (t_mmd){.min = cols->min, .max = cols->max};
	return (result);
}

int	bounding_boxes_intersect(t_segm *segm, t_segm *side)
{
	t_rect	*r_segm;
	t_rect	*r_side;

	r_segm = rectangularize(\
		integral_compare(segm->b->row, segm->e->row, &(t_mmd){0, 0}), \
		integral_compare(segm->b->col, segm->e->col, &(t_mmd){0, 0}), \
		&(t_rect){(t_mmd){0, 0}, (t_mmd){0, 0}});
	r_side = rectangularize(\
		integral_compare(side->b->row, side->e->row, &(t_mmd){0, 0}), \
		integral_compare(side->b->col, side->e->col, &(t_mmd){0, 0}), \
		&(t_rect){(t_mmd){0, 0}, (t_mmd){0, 0}});
	return (overlaps_2d(r_segm, r_side));
}

t_l_pt	*calculate_segment_intersection(t_segm *segm, t_segm *side, \
	t_l_pt *l_pt)
{
	(void)segm;
	(void)side;

	return (l_pt);
}

t_l_pt	*intersect(t_segm *segm, t_segm *side)
{
	if (bounding_boxes_intersect(segm, side))
	{
		return (calculate_segment_intersection(segm, side, \
			&(t_l_pt){.row = NO_INTERSECTION, .col = NO_INTERSECTION}));
	}
	return (&(t_l_pt){.row = NO_INTERSECTION, .col = NO_INTERSECTION});
}

void	init_segs(t_segm segs[4], int initialized)
{
	if (initialized == FALSE)
	{
		segs[TOP] = (t_segm){
			&(t_pt){.row = 0, .col = 0},
			&(t_pt){.row = 0, .col = WIN_WIDTH - 1}
		};
		segs[RIGHT] = (t_segm){
			&(t_pt){.row = 0, .col = WIN_WIDTH - 1},
			&(t_pt){.row = WIN_HEIGHT - 1, .col = WIN_WIDTH - 1}
		};
		segs[BOTTOM] = (t_segm){
			&(t_pt){.row = WIN_HEIGHT - 1, .col = 0},
			&(t_pt){.row = WIN_HEIGHT - 1, .col = WIN_WIDTH - 1}
		};
		segs[LEFT] = (t_segm){
			&(t_pt){.row = 0, .col = 0},
			&(t_pt){.row = WIN_HEIGHT - 1, .col = 0}
		};
		initialized = TRUE;
	}
}

t_pt	*l_pt_to_pt(t_l_pt *l_pt, t_pt *result)
{
	if (l_pt->row != NO_INTERSECTION && l_pt->col != NO_INTERSECTION)
		return (result = (t_pt){.row = (int)l_pt->row, .col = (int)l_pt->col});
	return (NULL);
}

void	set_intersection(t_segm *s, t_segm segs[4], int initialized, \
	t_pt ssi[4])
{
	t_pt	*intersection;

	intersection = l_pt_to_pt(intersect(s, &segs[TOP], &(t_l_pt){0, 0}), \
		&(t_pt){0, 0});
	if (intersection != NULL)
		ssi[TOP] = intersection;
	intersection = l_pt_to_pt(intersect(s, &segs[RIGHT], &(t_l_pt){0, 0}), \
		&(t_pt){0, 0});
	if (intersection != NULL)
		ssi[RIGHT] = intersection;
	intersection = l_pt_to_pt(intersect(s, &segs[BOTTOM], &(t_l_pt){0, 0}), \
		&(t_pt){0, 0});
	if (intersection != NULL)
		ssi[BOTTOM] = intersection;
	interaction = l_pt_to_pt(intersect(s, &segs[LEFT], &(t_l_pt){0, 0}), \
		&(t_pt){0, 0});
	if (intersection != NULL)
		ssi[LEFT] = intersection;
}

void	calculate_screen_segment_intersections(t_segm *s, \
	t_pt screen_segment_intersections[4])
{
	static t_segm	segs[4];
	static int		initialized = FALSE;

	init_segs(segs, initialized);
	set_intersections(s, segs, initialized, screen_segment_intersections);
}

t_pt	*crop_segment(t_segm *s)
{
	t_pt	screen_segment_intersections[4];
	int		out_of_bounds;

	out_of_bounds = FALSE;
	calculate_screen_segment_intersections(s, screen_segment_intersections);
	if (out_of_bounds == TRUE)
		return (NULL);
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
				draw_line(crop_segment(&(t_segm){&p0, &p1}), \
					&(t_prog){mlx, fdf, 0, 0}, \
					&(t_segm){&point, &(t_pt){.row = point.row, \
					.col = point.col + 1}});
			}
			if (point.row + 1 < fdf->map.line_count)
			{
				project(&p1, &(t_pt){.row = point.row + 1, \
					.col = point.col}, fdf);
				draw_line(crop_segment(&(t_segm){&p0, &p1}), \
					&(t_prog){mlx, fdf, 0, 0}, \
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
