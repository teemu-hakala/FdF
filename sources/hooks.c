/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 08:30:31 by thakala           #+#    #+#             */
/*   Updated: 2022/03/30 13:39:24 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	hook_all(t_mlx *mlx, t_fdf *fdf)
{
	mlx_key_hook(mlx->win, key_handler, (void *)fdf);
	mlx_hook(mlx->win, ON_DESTROY, 0, close_success, (void *)fdf);
}
