/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colours.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 15:36:02 by thakala           #+#    #+#             */
/*   Updated: 2022/04/06 11:21:45 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static double	skew(double min, double percentage, double max)
{
	return (min + percentage * (1 - min) / max);
}

int	get_colour(double percentage, t_segm *pts, t_fdf *fdf)
{
	int		max_abs_height;
	double	height_percentage;
	int		colour_temp;
	int		alt_div;

	max_abs_height = get_altitude(\
		abs_max(fdf->map.lines[pts->b->row].line[pts->b->col], \
				fdf->map.lines[pts->e->row].line[pts->e->col]), fdf);
	max_abs_height += !max_abs_height;
	alt_div = get_altitude(fdf->map.height.max - fdf->map.height.min, fdf);
	height_percentage = (double)max_abs_height / \
		(alt_div + !alt_div * max_abs_height);
	if (fdf->map.lines[pts->b->row].line[pts->b->col] \
		!= fdf->map.lines[pts->e->row].line[pts->e->col])
		colour_temp = (int)(0xFF * \
			skew(LOWEST, percentage * height_percentage, HIGHEST)) \
			<< fdf->colour_theme;
	else
		colour_temp = (int)(0xFF * height_percentage) << fdf->colour_theme;
	if (colour_temp != 0)
		return (colour_temp);
	return ((int)(0xFF * LOWEST) << fdf->colour_theme);
}
