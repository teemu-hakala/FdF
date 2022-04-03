/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 18:04:22 by thakala           #+#    #+#             */
/*   Updated: 2022/04/03 14:42:46 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_colour_theme(t_prog *prog)
{
	if (prog->fdf->colour_theme == RED)
		prog->fdf->colour_theme = GREEN;
	else if (prog->fdf->colour_theme == GREEN)
		prog->fdf->colour_theme = BLUE;
	else if (prog->fdf->colour_theme == BLUE)
		prog->fdf->colour_theme = RED;
}

void	rotate_projection(t_prog *prog)
{
	if (prog->fdf->proj == PROJ_PARALLEL)
		prog->fdf->proj = PROJ_ISOMETRIC;
	else if (prog->fdf->proj == PROJ_ISOMETRIC)
		prog->fdf->proj = PROJ_PARALLEL;
}

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

int	zoomer(int dir, int zoom)
{
	if (dir == ZOOM_IN)
	{
		if ((zoom << 1) >> 1 == zoom)
			return (zoom << 1);
	}
	else if (dir == ZOOM_OUT)
		if ((zoom >> 1) << 1 == zoom)
			return (zoom >> 1);
	return (zoom);
}

void	pan(t_prog *prog)
{
	prog->fdf->offset = \
		(t_pt) \
		{\
			.row = prog->fdf->offset.row + prog->mse->diff.row, \
			.col = prog->fdf->offset.col + prog->mse->diff.col \
		};
}

// void	offsetter(int prev_zoom, t_pt *mse, t_prog *prog)
// {
// 	double	scalar;
// 	t_pt	vector;

// 	scalar = 1.0;
// 	if (prog->fdf->zoom != 0)
// 		scalar = (double)prog->fdf->zoom / prev_zoom;
// printf("prev_zoom / prog->fdf->zoom: %d / %d\n", prev_zoom, prog->fdf->zoom);
// printf("scalar: %.15f\n", scalar);
// 	vector = (t_pt){.row = (int)(scalar * (mse->row - prog->fdf->offset.row)), \
// 		.col = (int)(scalar * (mse->col - prog->fdf->offset.col))};
// printf("vector.row: %d, vector.col: %d\n", vector.row, vector.col);
// printf("mse->row: %d, mse->col: %d\n", mse->row, mse->col);
// 	prog->fdf->offset = vector;
// printf("offset.row: %d, offset.col: %d\n", prog->fdf->offset.row, prog->fdf->offset.col);

// /*printf("mse->row: %d, WIN_HEIGHT: %d, prog->fdf->zoom: %d, prev_zoom: %d, prog->fdf->map.line_count: %d\n", \
// 	mse->row, WIN_HEIGHT, prog->fdf->zoom, prev_zoom, prog->fdf->map.line_count);
// printf("mse->col: %d, WIN_WIDTH: %d, prog->fdf->zoom: %d, prev_zoom: %d, prog->fdf->map.max_point_count: %d\n\n", \
// 	mse->col, WIN_WIDTH, prog->fdf->zoom, prev_zoom, prog->fdf->map.max_point_count);
// 	vector = (t_pt){.row = (int)((double)prog->fdf->origin.row - ((double)mse->row / WIN_HEIGHT * ((prog->fdf->zoom - prev_zoom) * prog->fdf->map.line_count))),
// 		.col = (int)((double)prog->fdf->origin.col - ((double)mse->col / WIN_WIDTH * ((prog->fdf->zoom - prev_zoom) * prog->fdf->map.max_point_count)))};
// draw_debug_line(&prog->fdf->origin, &vector, prog->fdf, &prog->mlx->img);
// printf("vector.row: %d, vector.row: %d\n", vector.row, vector.col);
// printf("offset.row: %d, offset.col: %d\n", prog->fdf->offset.row, prog->fdf->offset.col);
// 	prog->fdf->offset = vector;
// printf("offset.row: %d, offset.col: %d\n\n", prog->fdf->offset.row, prog->fdf->offset.col);*/
// }

/*void	offsetter(int prev_zoom, t_pt *mse, t_prog *prog)
{
	double	scalar;
	t_pt	vector;

	scalar = 1.0;
	if (prev_zoom != 0)
		scalar = (double)prog->fdf->zoom / prev_zoom;
	vector = (t_pt){.row = (int)(scalar * (mse->row - prog->fdf->offset.row)), \
		.col = (int)(scalar * (mse->col - prog->fdf->offset.col))};
	prog->fdf->offset = vector;
}*/

t_pt	*screen_to_world(t_pt *screen, t_prog *prog, int zoom)
{
	*screen = \
		(t_pt){.row = (screen->row - prog->fdf->offset.row) / zoom, \
		.col = (screen->col - prog->fdf->offset.col) / zoom};
	return (screen);
}

void	offsetter(t_pt *mse, t_prog *prog, int prev_zoom)
{
	t_pt	*prev_mse_wrld;
	t_pt	*mse_wrld;

	prev_mse_wrld = \
		screen_to_world(&(t_pt){.row = mse->row, .col = mse->col}, prog, prev_zoom);
	mse_wrld = \
		screen_to_world(&(t_pt){.row = mse->row, .col = mse->col}, prog, prog->fdf->zoom);
printf("prev_mse_wrld->row: %d prev_mse_wrld->col: %d\n", prev_mse_wrld->row, prev_mse_wrld->col);
printf("mse_wrld->row: %d mse_wrld->col: %d\n", mse_wrld->row, mse_wrld->col);
	prog->fdf->offset = (t_pt){.row = get_ordinate(mse_wrld->row - prev_mse_wrld->row, prog->fdf), \
		.col = get_abscissa(mse_wrld->col - prev_mse_wrld->col, prog->fdf)};
}

int	mouse_handler_down(int button, int x, int y, t_prog *prog)
{
	int		prev_zoom;

	if (button == LEFT_CLICK)
	{
		prog->mse->prev = prog->mse->curr;
		prog->mse->curr = (t_pt){.row = y, .col = x};
		prog->mse->isdown = TRUE;
		return (mouse_handler(button, x, y, prog));
	}
	prev_zoom = prog->fdf->zoom;
	if (button == SCROLL_UP)
	{
		// prog->fdf->offset = (t_pt){0,0};
		if (prog->key->cmd_toggled == TRUE)
		{
			prog->fdf->height += HEIGHT_ADDITION / prog->fdf->zoom;
		}
		else
		{
			prog->fdf->zoom = zoomer(ZOOM_IN, prog->fdf->zoom);
			offsetter(&(t_pt){.row = y, .col = x}, prog, prev_zoom);
			//offsetter(prev_zoom, &(t_pt){.row = y, .col = x}, prog);
		}
		draw(prog->mlx, prog->fdf);
		return (RETURN_SUCCESS);
	}
	if (button == SCROLL_DOWN)
	{
		// prog->fdf->offset = (t_pt){0,0};
		if (prog->key->cmd_toggled == TRUE)
		{
			prog->fdf->height -= HEIGHT_ADDITION / prog->fdf->zoom;
		}
		else
		{
			prog->fdf->zoom = zoomer(ZOOM_OUT, prog->fdf->zoom);
			offsetter(&(t_pt){.row = y, .col = x}, prog, prev_zoom);
			//offsetter(prev_zoom, &(t_pt){.row = y, .col = x}, prog);
		}
		draw(prog->mlx, prog->fdf);
		return (RETURN_SUCCESS);
	}
	return (RETURN_ERROR);
}

/*
	Advanced mouse locking, from which you escape by left clicking.
	Mouse is centralised whenever movement with left click down is detected.

		int		mlx_mouse_move(void *win_ptr, int x, int y);
		int		mlx_do_key_autorepeaton(void *mlx_ptr);
*/

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
