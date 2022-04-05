/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 15:35:02 by thakala           #+#    #+#             */
/*   Updated: 2022/04/05 19:36:37 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_projection_angle(t_fdf *fdf)
{
	return (PROJ_ISOMETRIC + DIFF_ISO_MIL * !!(fdf->proj == PROJ_MILITARY));
}

void	project(t_pt *dst, t_pt *src, t_fdf *fdf)
{
	int		screen_row;
	int		screen_col;
	int		ordinate;
	int		abscissa;
	int		altitude;

	if (fdf->proj == PROJ_PARALLEL)
	{
		*dst = (t_pt){.row = get_ordinate(src->row, fdf) - fdf->origin.row, \
			.col = get_abscissa(src->col, fdf) - fdf->origin.col};
		return ;
	}
	ordinate = src->row * fdf->zoom - fdf->origin.row;//get_ordinate(src->row, fdf);
	abscissa = src->col * fdf->zoom - fdf->origin.col;//get_abscissa(src->col, fdf);
	altitude = get_altitude(fdf->map.lines[src->row].line[src->col], fdf);
	screen_row = (int)((double)(-altitude) \
		+ (abscissa + ordinate) * sin(M_PI * get_projection_angle(fdf) / 180));
	screen_col = (int)((double)(abscissa - ordinate) \
		*cos(M_PI * get_projection_angle(fdf) / 180));
	*dst = (t_pt){.row = screen_row + fdf->offset.row, \
		.col = screen_col + fdf->offset.col};
}
