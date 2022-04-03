/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 15:27:56 by thakala           #+#    #+#             */
/*   Updated: 2022/04/03 15:28:09 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	zoomer(int dir, int zoom)
{
	if (dir == ZOOM_IN)
	{
		if ((zoom << 1) >> 1 == zoom)
			return (zoom << 1);
	}
	else if (dir == ZOOM_OUT)
		if ((zoom >> 1) << 1 == zoom)
			return (zoom >> 1);
	return (zoom);
}

void	pan(t_prog *prog)
{
	prog->fdf->offset = \
		(t_pt) \
		{\
			.row = prog->fdf->offset.row + prog->mse->diff.row, \
			.col = prog->fdf->offset.col + prog->mse->diff.col \
		};
}

t_pt	*screen_to_world(t_pt *screen, t_prog *prog, int zoom)
{
	*screen = \
		(t_pt){.row = (screen->row - prog->fdf->offset.row) / zoom, \
		.col = (screen->col - prog->fdf->offset.col) / zoom};
	return (screen);
}

void	offsetter(t_pt *mse, t_prog *prog, int prev_zoom)
{
	t_pt	*prev_mse_wrld;
	t_pt	*mse_wrld;

	prev_mse_wrld = screen_to_world(&(t_pt){.row = mse->row, .col = mse->col}, \
		prog, prev_zoom);
	mse_wrld = screen_to_world(&(t_pt){.row = mse->row, .col = mse->col}, \
		prog, prog->fdf->zoom);
}
