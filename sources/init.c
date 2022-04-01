/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 09:18:22 by thakala           #+#    #+#             */
/*   Updated: 2022/04/01 19:16:38 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	init_mlx(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	if (mlx->mlx == NULL)
		exit_msg("Minilibx initialization failure (is NULL);", EXIT_ERROR);
	mlx->win = mlx_new_window(mlx->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_NAME);
	if (mlx->win == NULL)
		exit_msg("Window pointer is NULL!", EXIT_ERROR);
}

static void	init_fdf(t_fdf *fdf)
{
	fdf->origin = (t_pt){.row = WIN_HEIGHT / 2, .col = WIN_WIDTH / 2};
	fdf->color = COLOR_DEF;
	fdf->zoom = 10;
	fdf->offset = (t_pt){.row = WIN_HEIGHT / 8, .col = WIN_WIDTH / 8};
}

static void	init_mse(t_prog *prog)
{
	prog->mse->prev = prog->fdf->origin;
	prog->mse->curr = prog->fdf->origin;
	prog->mse->diff = (t_l_pt){.row = 0LL, .col = 0LL};
}

void	init_req(t_prog *prog)
{
	init_mlx(prog->mlx);
	init_fdf(prog->fdf);
	init_mse(prog);
}
