/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 10:22:55 by thakala           #+#    #+#             */
/*   Updated: 2022/04/05 20:14:32 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	max(double d0, double d1)
{
	if (d0 > d1)
		return (d0);
	return (d1);
}

int	abs_max(int i0, int i1)
{
	i1 *= (i1 < 0) * -1 | 0x1;
	i0 *= (i0 < 0) * -1 | 0x1;
	if (i1 > i0)
		return (i1);
	return (i0);
}

int	in_range(int lowest, int value, int upto)
{
	return (lowest <= value && value < upto);
}
