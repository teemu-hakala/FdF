/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 15:26:27 by thakala           #+#    #+#             */
/*   Updated: 2022/04/04 19:54:16 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	mouse_handler_scroll_up(t_prog *prog, t_pt *mse)
{
	int		prev_zoom;

	if (prog->key->cmd_toggled == TRUE)
	{
		prog->fdf->height += HEIGHT_ADDITION / prog->fdf->zoom;
	}
	else
	{
		prev_zoom = prog->fdf->zoom;
		prog->fdf->zoom = zoomer(ZOOM_IN, prog->fdf->zoom);
		init_origin(prog->fdf);
		offsetter(mse, prog, prev_zoom);
	}
	draw(prog->mlx, prog->fdf);
	return (RETURN_SUCCESS);
}

int	mouse_handler_scroll_down(t_prog *prog, t_pt *mse)
{
	int		prev_zoom;

	if (prog->key->cmd_toggled == TRUE)
	{
		prog->fdf->height -= HEIGHT_ADDITION / prog->fdf->zoom;
	}
	else
	{
		prev_zoom = prog->fdf->zoom;
		prog->fdf->zoom = zoomer(ZOOM_OUT, prog->fdf->zoom);
		init_origin(prog->fdf);
		offsetter(mse, prog, prev_zoom);
	}
	draw(prog->mlx, prog->fdf);
	return (RETURN_SUCCESS);
}

int	mouse_handler_down(int button, int x, int y, t_prog *prog)
{
	if (button == LEFT_CLICK)
	{
		prog->mse->prev = prog->mse->curr;
		prog->mse->curr = (t_pt){.row = y, .col = x};
		prog->mse->isdown = TRUE;
		return (mouse_handler(button, x, y, prog));
	}
	if (button == SCROLL_UP)
		return (mouse_handler_scroll_up(prog, &(t_pt){.row = y, .col = x}));
	if (button == SCROLL_DOWN)
		return (mouse_handler_scroll_down(prog, &(t_pt){.row = y, .col = x}));
	return (RETURN_ERROR);
}

int	mouse_handler_move(int x, int y, t_prog *prog)
{

	if (prog->mse->isdown == TRUE)
	{
		prog->mse->prev = prog->mse->curr;
		prog->mse->diff = (t_pt){.row = y - prog->mse->curr.row, \
			.col = x - prog->mse->curr.col};
		pan(prog);
		prog->mse->curr = (t_pt){.row = y, .col = x};
		return (mouse_handler(MOVE, x, y, prog));
	}
	return (RETURN_ERROR);
}

int	mouse_handler_up(int button, int x, int y, t_prog *prog)
{
	if (button == LEFT_CLICK)
	{
		prog->mse->prev = prog->mse->curr;
		prog->mse->isdown = FALSE;
		return (mouse_handler(button, x, y, prog));
	}
	return (RETURN_ERROR);
}
