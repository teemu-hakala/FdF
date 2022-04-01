/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 18:04:22 by thakala           #+#    #+#             */
/*   Updated: 2022/04/01 17:44:03 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_handler(int key, void *param)
{
	t_prog	*prog;

	(void) key;
	prog = (t_prog *)param;
printf("fdf->origin.row %d\n", prog->fdf->origin.row);
	if (key == KEY_ESC)
		exit_msg("Escape!", 0);
	ft_putnbr(key);
	ft_putchar('\n');
	return (0);
}

int	mouse_handler(int button, int x, int y, t_prog *prog)
{
printf("MOUSE_KEY: %d\n", button);
printf("prog->fdf->zoom: %d\n", prog->fdf->zoom);
printf("x: %d, y: y %d\n", x, y);
	if (button == SCROLL_UP)
	{
		prog->fdf->zoom <<= 1;
		draw(prog);
	}
	else if (button == SCROLL_DOWN)
	{
		prog->fdf->zoom >>= 1;
		draw(prog);
	}
	return (RETURN_SUCCESS);
}
