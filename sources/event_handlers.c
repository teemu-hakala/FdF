/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 18:04:22 by thakala           #+#    #+#             */
/*   Updated: 2022/04/05 09:20:18 by thakala          ###   ########.fr       */
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
		reset_origin(prog->fdf);
		rotate_projection(prog);
		draw(prog->mlx, prog->fdf);
	}
	ft_putnbr(key);
	ft_putchar('\n');
	return (0);
}

int	mouse_handler(int button, int x, int y, t_prog *prog)
{
	(void) button;
	(void) x;
	(void) y;
	draw(prog->mlx, prog->fdf);
	return (RETURN_SUCCESS);
}
