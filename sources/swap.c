/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 15:34:30 by thakala           #+#    #+#             */
/*   Updated: 2022/04/03 15:34:41 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
