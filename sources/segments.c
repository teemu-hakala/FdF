/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segments.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 08:49:23 by thakala           #+#    #+#             */
/*   Updated: 2022/04/09 12:50:46 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
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
		integral_comparator(segm->b->row, segm->e->row, &(t_mmd){0, 0}), \
		integral_comparator(segm->b->col, segm->e->col, &(t_mmd){0, 0}), \
		&(t_rect){(t_mmd){0, 0}, (t_mmd){0, 0}});
	r_side = rectangularize(\
		integral_comparator(side->b->row, side->e->row, &(t_mmd){0, 0}), \
		integral_comparator(side->b->col, side->e->col, &(t_mmd){0, 0}), \
		&(t_rect){(t_mmd){0, 0}, (t_mmd){0, 0}});
	return (overlaps_2d(r_segm, r_side));
}

t_l_pt	*csi_case_a(t_segm *a, t_segm *b, t_l_pt *l_pt)
{

}

t_l_pt	*csi_case_b(t_segm *a, t_segm *b, t_l_pt *l_pt)
{

}

t_l_pt	*csi_case_c(t_segm *a, t_segm *b, t_l_pt *l_pt)
{

}

t_l_pt	*calculate_segment_intersection(t_segm *segm, t_segm *side, \
	t_l_pt *l_pt)
{
	(void)segm;
	(void)side;
	csi_case_a(segm, side, l_pt);
	csi_case_b(segm, side, l_pt);
	csi_case_c(segm, side, l_pt);
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

// explicitly disallow truncation of set bits in long transformation?:
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

char	select_intersections(t_pt ssi[4])
{
	char	number_of_intersections;
	char	i;
	number_of_intersections = 0;

	i = 0;
	while (i < 4)
	{
		if (ssi[i] != NULL)
		{
			ssi[number_of_intersections++] = ssi[i];
			ssi[i] = NULL;
		}
		i++;
	}
	return (number_of_intersections);
}
*/
int	east_of_west(t_pt *point)
{
	return (point->col >= 0);
}

int south_of_north(t_pt *point)
{
	return (point->row >= 0);
}

int west_of_east(t_pt *point)
{
	return (point->col < WIN_WIDTH);
}

int north_of_south(t_pt *point)
{
	return (point->row < WIN_HEIGHT);
}

int	in_view(t_pt *point)
{
	return (east_of_west(point) \
		&& south_of_north(point) \
		&& west_of_east(point) \
		&& north_of_south(point));
}

/// Must possibly swap the segment begin and end points to match the order...
// Since the segments start from the same pixel, intersections might actually
//	be more than 2 at {.row = 0, .col = 0}...
t_segm	*crop_segment(t_segm *s, t_segm *o)
{
	//t_pt	screen_segment_intersections[4];
	//int		out_of_bounds;
	//int		intersection_count;

	if (in_view(s->b))
		return (s);
	if (in_view(s->e))
	{
		swap_points(&s->b, &s->e, DO_SWAP);
		swap_points(&o->b, &o->e, DO_SWAP);
		return (s);
	}
	/*
	out_of_bounds = FALSE;
	calculate_screen_segment_intersections(s, screen_segment_intersections);
	intersection_count = select_intersections(screen_segment_intersections);
	if (intersection_count == 0)
		out_of_bounds = TRUE;
	else if (intersection_count == 1)
	{
		s->b = (t_pt){.row = screen_segment_intersections[0].row, \
			.col = screen_segment_intersections[0].col};
		s->e = (t_pt){.row = screen_segment_intersections[0].row, \
			.col = screen_segment_intersections[0].col};
	}
	else if (intersection_count == 2)
	{
		s->b = (t_pt){.row = screen_segment_intersections[0].row, \
			.col = screen_segment_intersections[0].col};
		s->e = (t_pt){.row = screen_segment_intersections[1].row, \
			.col = screen_segment_intersections[1].col};
	}
	else if (intersection_count < 0 || intersection_count > 2)
		exit_msg("intersection_count too high or too low\n", EXIT_ERROR);
	if (out_of_bounds == TRUE)
		return (NULL);*/
	return (s);
}

void	segment_feeder(t_mlx *mlx, t_fdf *fdf, t_pt *point)
{
	t_pt	p0;
	t_pt	p1;
	t_segm	*original;

	project(&p0, point, fdf);
	if (point->col + 1 < fdf->map.lines[point->row].point_count)
	{
		project(&p1, &(t_pt){.row = point->row, \
			.col = point->col + 1}, fdf);
		original = &(t_segm){point, &(t_pt){.row = point->row, \
			.col = point->col + 1}};
		draw_line(crop_segment(&(t_segm){&p0, &p1}, original), \
			&(t_prog){mlx, fdf, 0, 0}, \
			original);
	}
	if (point->row + 1 < fdf->map.line_count)
	{
		project(&p1, &(t_pt){.row = point->row + 1, \
			.col = point->col}, fdf);
		original = &(t_segm){point, &(t_pt){.row = point->row + 1, \
			.col = point->col}};
		draw_line(crop_segment(&(t_segm){&p0, &p1}, original), \
			&(t_prog){mlx, fdf, 0, 0}, \
			original);
	}
}
/*
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

t_mmd	*integral_comparator(int i0, int i1, t_mmd *minmaxindir)
{
	*minmaxindir = (t_mmd){.min = i0, .max = i1};
	if (i0 > i1)
		*minmaxindir = (t_mmd){.min = i1, .max = i0};
	return (minmaxindir);
}
*/
