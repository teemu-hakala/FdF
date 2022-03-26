/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 14:07:37 by thakala           #+#    #+#             */
/*   Updated: 2022/03/26 18:19:15 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	void	*mlx;
	void	*win;

	(void) argc;
	(void) argv;
	mlx = mlx_init();
	win = mlx_new_window(mlx, WIN_WIDTH, WIN_HEIGHT, WIN_NAME);
	if (win == NULL)
		exit_msg("", 1);
	mlx_pixel_put(mlx, win, WIN_WIDTH / 2, WIN_HEIGHT / 2, 0xFFFFFF);
	mlx_key_hook(win, key_handler, (void *)0);
	mlx_loop(mlx);
}
