/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 18:04:22 by thakala           #+#    #+#             */
/*   Updated: 2022/04/03 15:27:49 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_handler(int key, t_prog *prog)
{
	if (key == KEY_ESC)
		exit_msg("Escape!", 0);
	if (key == KEY_L_CMD || key == KEY_R_CMD)
		prog->key->cmd_toggled = !prog->key->cmd_toggled;
	if (key == KEY_C_OLOUR)
	{
		rotate_colour_theme(prog);
		draw(prog->mlx, prog->fdf);
	}
	if (key == KEY_P_ROJECTION)
	{
		rotate_projection(prog);
		draw(prog->mlx, prog->fdf);
	}
	ft_putnbr(key);
	ft_putchar('\n');
	return (0);
}

int	mouse_handler(int button, int x, int y, t_prog *prog)
{
printf("MOUSE_KEY: %d\n", button);
printf("prog->fdf->zoom: %d\n", prog->fdf->zoom);
printf("prog->fdf->offset.row: %d, prog->fdf->offset.row: %d\n",
prog->fdf->offset.row, prog->fdf->offset.col);
printf("x: %d, y: y %d\n", x, y);
	if (button == SCROLL_UP)
	{
		prog->fdf->zoom = zoomer(ZOOM_IN, prog->fdf->zoom);
		draw(prog->mlx, prog->fdf);
		return (RETURN_SUCCESS);
	}
	if (button == SCROLL_DOWN)
	{
		prog->fdf->zoom = zoomer(ZOOM_OUT, prog->fdf->zoom);
		draw(prog->mlx, prog->fdf);
		return (RETURN_SUCCESS);
	}
	draw(prog->mlx, prog->fdf);
	return (RETURN_SUCCESS);
}
