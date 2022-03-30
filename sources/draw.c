/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 09:08:03 by thakala           #+#    #+#             */
/*   Updated: 2022/03/30 13:38:31 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
	<placeholder for a definitive comment>
*/

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = (unsigned int)color;
}

void	init_img(t_mlx *mlx)
{
	mlx->img.img = mlx_new_image(mlx->mlx, WIN_WIDTH, WIN_HEIGHT);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img.bits_per_pixel, \
		&mlx->img.line_length, &mlx->img.endian);
}

void	debug_printer(t_fdf_map *map)
{
	for (uint64_t line = 0; line < map->line_count; line++)
	{
		for (uint64_t point = 0; point < map->lines[line].point_count; point++)
		{
			printf("%d ", map->lines[line].line[point]);
		}
		printf("\n");
	}
	printf("\n");
}

void	draw(t_mlx *mlx, t_fdf *fdf)
{
	debug_printer(&fdf->map);
	init_img(mlx);
	my_mlx_pixel_put(&mlx->img, 5, 5, 0x00FF0000);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
	mlx_destroy_image(mlx->mlx, mlx->img.img);
}
