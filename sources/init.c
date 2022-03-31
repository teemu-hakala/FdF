/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 09:18:22 by thakala           #+#    #+#             */
/*   Updated: 2022/03/31 09:13:48 by thakala          ###   ########.fr       */
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

void	init_map(t_fdf_map *map)
{
	(void) map;
	//map->line_count = (uint64_t)INITIAL_LINE_COUNT;
	//map->map = (int **)malloc(sizeof(int *) * (map->line_count + 1));
}

void	init_req(t_mlx *mlx, t_fdf *fdf)
{
	init_mlx(mlx);
	init_fdf(fdf);
	//init_map(&fdf->map);
}
