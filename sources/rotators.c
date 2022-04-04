/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotators.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 15:27:29 by thakala           #+#    #+#             */
/*   Updated: 2022/04/04 12:09:22 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_colour_theme(t_prog *prog)
{
	if (prog->fdf->colour_theme == RED)
		prog->fdf->colour_theme = GREEN;
	else if (prog->fdf->colour_theme == GREEN)
		prog->fdf->colour_theme = BLUE;
	else if (prog->fdf->colour_theme == BLUE)
		prog->fdf->colour_theme = RED;
}

void	rotate_projection(t_prog *prog)
{
	if (prog->fdf->proj == PROJ_PARALLEL)
		prog->fdf->proj = PROJ_ISOMETRIC;
	else if (prog->fdf->proj == PROJ_ISOMETRIC)
		prog->fdf->proj = PROJ_MILITARY;
	else if (prog->fdf->proj == PROJ_MILITARY)
		prog->fdf->proj = PROJ_PARALLEL;
	init_offset(prog->fdf);
}
