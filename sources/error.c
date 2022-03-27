/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 18:16:14 by thakala           #+#    #+#             */
/*   Updated: 2022/03/27 11:18:57 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	exit_msg(const char *msg, int val)
{
	ft_putstr(msg);
	exit(val);
}

int	close_success(void)
{
	exit_msg("\033[0;31mGreat success!\033[0m\n", 0);
	return (0);
}
