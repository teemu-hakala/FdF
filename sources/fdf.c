/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 14:07:37 by thakala           #+#    #+#             */
/*   Updated: 2022/04/02 20:34:19 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	static t_mlx	mlx;
	static t_fdf	fdf;
	static t_mse	mse;
	t_prog			prog;

	if (argc != 2)
		exit_msg("usage: ./fdf <filename>.fdf\n", EXIT_ERROR);
	prog = (t_prog){.mlx = &mlx, .fdf = &fdf, .mse = &mse};
	parse(*(argv + 1), &prog.fdf->map);
	init_req(&prog);
	hook_all(&prog);
	draw(&mlx, &fdf);
	mlx_loop(prog.mlx->mlx);
}
