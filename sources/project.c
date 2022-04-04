/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 15:35:02 by thakala           #+#    #+#             */
/*   Updated: 2022/04/04 23:15:43 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_projection_angle(t_fdf *fdf)
{
	return (30 + 15 * !!(fdf->proj == PROJ_MILITARY));
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
		*dst = (t_pt){.row = get_ordinate(src->row, fdf), \
			.col = get_abscissa(src->col, fdf)};
		return ;
	}
	ordinate = get_ordinate(src->row, fdf);
	abscissa = get_abscissa(src->col, fdf);
	altitude = get_altitude(fdf->map.lines[src->row].line[src->col], fdf);
	screen_row = (int)((double)(-altitude) \
		+ (abscissa + ordinate) * sin(M_PI * get_projection_angle(fdf) / 180));
	screen_col = (int)((double)(abscissa - ordinate) \
		*cos(M_PI * get_projection_angle(fdf) / 180));
	*dst = (t_pt){.row = screen_row, .col = screen_col};
}

// void	project_offset(t_pt *dst, t_pt *src, t_fdf *fdf)
// {
// 	int		screen_row;
// 	int		screen_col;
// 	int		ordinate;
// 	int		abscissa;
// 	int		altitude;

// 	if (fdf->proj == PROJ_PARALLEL)
// 	{
// 		*dst = (t_pt){.row = src->row, .col = src->col};
// 		return ;
// 	}
// 	ordinate = fdf->offset.row;
// 	abscissa = fdf->offset.col;
// 	altitude = 0;
// 	screen_row = (int)((double)(-altitude) \
// 		+ (abscissa + ordinate) * sin(M_PI * get_projection_angle(fdf) / 180));
// 	screen_col = (int)((double)(abscissa - ordinate) \
// 		*cos(M_PI * get_projection_angle(fdf) / 180));
// 	*dst = (t_pt){.row = screen_row, .col = screen_col};
// }
