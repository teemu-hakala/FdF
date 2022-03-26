/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 18:04:22 by thakala           #+#    #+#             */
/*   Updated: 2022/03/26 18:23:20 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_handler(int key, void *param)
{
	(void) key;
	(void) param;
	ft_putnbr(key);
	ft_putchar('\n');
	if (key == KEY_ESC)
		exit_msg("", 0);
	return (0);
}
