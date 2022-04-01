/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 14:07:37 by thakala           #+#    #+#             */
/*   Updated: 2022/04/01 15:45:56 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*void	debug_function(t_mlx *mlx, t_fdf *fdf)
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
}*/

int	main(int argc, char **argv)
{
	static t_mlx	mlx;
	static t_fdf	fdf;
	// t_prog			*prog;
	t_prog			prog;

	if (argc != 2)
		exit_msg("usage: ./fdf <filename>.fdf\n", EXIT_ERROR);
	prog.mlx = &mlx;
	prog.fdf = &fdf;
	// init_map(&fdf.map);
	parse(*(argv + 1), &prog.fdf->map);
	init_req(&prog);
	//prog = (t_prog *)malloc(sizeof(t_prog));
	hook_all(&prog);
	//prog = &(t_prog){.mlx = &mlx, .fdf = &fdf};
	//hook_all(prog);
	//prog = (t_prog){.mlx = &mlx, .fdf = &fdf};
	//hook_all(&prog);
	//debug_function(&mlx, &fdf);
	//draw(&mlx, &fdf);
	draw(&prog);
	mlx_loop(prog.mlx->mlx);
}
