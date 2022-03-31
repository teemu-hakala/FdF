/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 18:04:22 by thakala           #+#    #+#             */
/*   Updated: 2022/03/31 22:06:08 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_handler(int key, void *param)
{
	(void) key;
	(void) param;
	if (key == KEY_ESC)
		exit_msg("Escape!", 0);
	ft_putnbr(key);
	ft_putchar('\n');
	return (0);
}

int	mouse_handler(int key, void *param)
{
	t_prog	*prog;

	prog = (t_prog *)param;
	if (key == SCROLL_UP)
	{
		prog->fdf->zoom *= 2;
		draw(prog->mlx, prog->fdf);
	}
	else if (key == SCROLL_DOWN)
	{
		prog->fdf->zoom /= 2;
		draw(prog->mlx, prog->fdf);
	}
printf("prog->fdf->zoom: %d\n", prog->fdf->zoom);
	return (RETURN_SUCCESS);
}
