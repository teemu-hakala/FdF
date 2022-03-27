/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 14:07:37 by thakala           #+#    #+#             */
/*   Updated: 2022/03/27 08:57:30 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

	# include <stdio.h>
void	init_req(t_mlx *mlx, t_fdf *fdf)
{
	mlx->mlx = mlx_init();
	if (mlx->mlx == NULL)
		exit_msg("Minilibx initialization failure (is NULL);", EXIT_ERROR);
	mlx->win = mlx_new_window(mlx, WIN_WIDTH, WIN_HEIGHT, WIN_NAME);
	if (mlx->win == NULL)
		exit_msg("Window pointer is NULL!", EXIT_ERROR);
	fdf->origin = (t_pt) { .row = WIN_HEIGHT / 2, .col = WIN_WIDTH / 2 };
	fdf->color = COLOR_DEF;
}

void	debug_function(t_mlx *mlx, t_fdf *fdf)
{
	int		i;

printf("%d %d %d\n", fdf->origin.col, fdf->origin.row, (int)fdf->color);
	i = 0;
	while (i < 100)
	{
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
	debug_function(&mlx, &fdf);
	hook_all(&mlx, &fdf);
	mlx_loop(mlx.mlx);
}
