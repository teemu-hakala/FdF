/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 08:30:31 by thakala           #+#    #+#             */
/*   Updated: 2022/04/01 16:35:00 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	hook_all(t_prog *prog)
{
	mlx_mouse_hook(prog->mlx->win, mouse_handler, prog);
	mlx_key_hook(prog->mlx->win, key_handler, prog);
	mlx_hook(prog->mlx->win, ON_DESTROY, 0, close_success, prog);
}
