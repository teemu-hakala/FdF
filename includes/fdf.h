/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 11:09:46 by thakala           #+#    #+#             */
/*   Updated: 2022/03/28 18:05:09 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h> // man 2 open
//# include <unistd.h> // man 2 read; man 2 write; man 2 close
# include <stdlib.h> // man 3 malloc; man 3 free; man 3 exit
//# include <stdio.h> // man 3 perror; man 3 strerror
//# include <math.h> // man 3 math

	#	 include <stdio.h>
# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"

# define WIN_HEIGHT 960
# define WIN_WIDTH 1280
# define WIN_NAME "FdF-thakala-0"

typedef enum e_color
{
	COLOR_DEF = 0xFFFFFF
}	t_color;

typedef struct s_point
{
	int		row;
	int		col;
}	t_pt;

//# define INITIAL_LINE_COUNT 0
# define INITIAL_LINE_LENGHT 55

typedef struct s_line
{
	int			*line;
	uint64_t	point_count;
	uint64_t	size;
}	t_line;

typedef struct s_map
{
	t_line		*lines;
	uint64_t	line_count;
	uint64_t	size;
	// int64_t	*line_lengths;
}	t_fdf_map;

typedef struct s_fdf
{
	t_pt		origin;
	t_color		color;
	t_fdf_map	map;
}	t_fdf;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		bytes_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	t_img	img;
}	t_mlx;

# define EXIT_ERROR 1
# define EXIT_SUCCESS 0

void	exit_msg(const char *msg, int val);
int		close_success(void);

enum e_event{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

enum e_key
{
	KEY_ESC = 53
};

int		key_handler(int key, void *param);
void	hook_all(t_mlx *mlx, t_fdf *fdf);

void	validate_line(char *line);

void	parse(char *filename, t_fdf_map *map);

void	init_req(t_mlx *mlx, t_fdf *fdf);
void	init_map(t_fdf_map *map);

void	my_mlx_pixel_put(t_img *data, int x, int y, int color);
void	draw(t_mlx *mlx, t_fdf *fdf);

#endif
