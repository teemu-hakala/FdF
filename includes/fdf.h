/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 11:09:46 by thakala           #+#    #+#             */
/*   Updated: 2022/03/26 18:21:29 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

//#include <fcntl.h> // man 2 open
//#include <unistd.h> // man 2 read; man 2 write; man 2 close
#include <stdlib.h> // man 3 malloc; man 3 free; man 3 exit
//#include <stdio.h> // man 3 perror; man 3 strerror
//#include <math.h> // man 3 math

# include "mlx.h"
# include "libft.h"

# define WIN_HEIGHT 960
# define WIN_WIDTH 1280
# define WIN_NAME "FdF-thakala-0"

typedef struct s_fdf
{

}	t_fdf;


typedef struct s_mlx
{

}	t_mlx;

# define EXIT_ERROR 1
# define EXIT_SUCCESS 0

void	exit_msg(const char *msg, int val);

enum e_key
{
	KEY_ESC = 53
};

int		key_handler(int key, void *param);

#endif
