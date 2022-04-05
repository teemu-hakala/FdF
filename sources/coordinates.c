/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinates.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 20:39:38 by thakala           #+#    #+#             */
/*   Updated: 2022/04/05 09:03:58 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_ordinate(int ordinate, t_fdf *fdf)
{
	return (ordinate * fdf->zoom + fdf->offset.row);
}

int	get_abscissa(int abscissa, t_fdf *fdf)
{
	return (abscissa * fdf->zoom + fdf->offset.col);
}

int	get_altitude(int altitude, t_fdf *fdf)
{
	return ((int)(altitude * fdf->zoom * fdf->height));
}
