/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 09:18:22 by thakala           #+#    #+#             */
/*   Updated: 2022/04/04 20:09:24 by thakala          ###   ########.fr       */
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

void	init_origin(t_fdf *fdf)
{
	fdf->origin = (t_pt){.row = get_ordinate(fdf->map.line_count, fdf) / 2, \
		.col = get_abscissa(fdf->map.max_point_count, fdf) / 2};
printf("fdf->origin.row: %d, fdf->origin.col: %d\n", fdf->origin.row, fdf->origin.col);
}

void	init_offset(t_fdf *fdf)
{
	fdf->offset = (t_pt){.row = WIN_HEIGHT / 2 - fdf->origin.row, \
		.col = WIN_WIDTH / 2 - fdf->origin.col};
}

void	init_map(t_fdf_map *map)
{
	map->height.max = INT_MIN;
	map->height.min = INT_MAX;
}

static void	init_fdf(t_fdf *fdf)
{
	fdf->zoom = (int)max(WIN_HEIGHT / (fdf->map.line_count * SPACING), \
		WIN_WIDTH / (fdf->map.max_point_count * SPACING));
	fdf->zoom += !fdf->zoom;
	init_origin(fdf);
	init_offset(fdf);
	fdf->color = COLOR_DEF;
	fdf->height = 1; //fdf->map.max_height;
	fdf->proj = PROJ_PARALLEL;
}

static void	init_mse(t_prog *prog)
{
	prog->mse->prev = prog->fdf->origin;
	prog->mse->curr = prog->fdf->origin;
	prog->mse->diff = (t_pt){.row = 0, .col = 0};
	prog->mse->isdown = FALSE;
}

void	init_req(t_prog *prog)
{
	init_mlx(prog->mlx);
	init_fdf(prog->fdf);
	init_mse(prog);
	mlx_do_key_autorepeaton(prog->mlx);
}

void	init_img(t_mlx *mlx, t_fdf *fdf)
{
	(void)fdf;
	mlx->img.img = mlx_new_image(mlx->mlx, WIN_WIDTH, WIN_HEIGHT);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img.bits_per_pixel, \
		&mlx->img.line_length, &mlx->img.endian);
	mlx->img.bytes_per_pixel = mlx->img.bits_per_pixel / 8;
}
