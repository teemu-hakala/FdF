/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 14:07:37 by thakala           #+#    #+#             */
/*   Updated: 2022/03/27 09:18:39 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

	# include <stdio.h>
	
void	debug_function(t_mlx *mlx, t_fdf *fdf)
{
	int		i;

	i = 0;
	while (i < 100)
	{
printf("%d %d %d\n", fdf->origin.col + i, fdf->origin.row + i, (int)fdf->color);
		mlx_pixel_put(mlx->mlx, mlx->win,
			fdf->origin.col + i, fdf->origin.row + i, (int)fdf->color);
		i++;
	}
}

int	main(int argc, char **argv)
{
	static t_mlx	mlx;
	static t_fdf	fdf;

	(void) argc;
	(void) argv;
	init_req(&mlx, &fdf);
	hook_all(&mlx, &fdf);
	debug_function(&mlx, &fdf);
	mlx_loop(mlx.mlx);
}
