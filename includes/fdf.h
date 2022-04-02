/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 11:09:46 by thakala           #+#    #+#             */
/*   Updated: 2022/04/02 20:41:37 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h> // man 2 open
//# include <unistd.h> // man 2 read; man 2 write; man 2 close
# include <stdlib.h> // man 3 malloc; man 3 free; man 3 exit
//# include <stdio.h> // man 3 perror; man 3 strerror
# include <math.h> // man 3 math

	#	 include <stdio.h>
# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"

# define WIN_HEIGHT 960
# define WIN_WIDTH 1280
# define WIN_NAME "FdF-thakala-0"

typedef enum e_color
{
	COLOR_DEF = 0xFFFFFF,
	COLOR_HEIGHT = 0xFF0000
}	t_color;

typedef struct s_point
{
	int		row;
	int		col;
}	t_pt;

typedef struct s_double_coordinate
{
	double	row;
	double	col;
}	t_db_pt;

typedef struct s_line
{
	int		*line;
	int		point_count;
	int		size;
}	t_line;

typedef struct s_map
{
	t_line		*lines;
	int			line_count;
	int			size;
	int			max_point_count;
	int			max_height;
}	t_fdf_map;

typedef struct s_mouse
{
	t_pt	prev;
	t_pt	curr;
	t_pt	diff;
	char	isdown;
}	t_mse;

typedef struct s_fdf
{
	t_pt		origin;
	t_color		color;
	t_pt		offset;
	int			height;
	int			zoom;
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

typedef struct s_program
{
	t_mlx	*mlx;
	t_fdf	*fdf;
	t_mse	*mse;
}	t_prog;

# define RETURN_SUCCESS 1
# define RETURN_ERROR 0

# define TRUE 1
# define FALSE 0

# define EXIT_ERROR 1
# define EXIT_SUCCESS 0

void	exit_msg(const char *msg, int val);
int		close_success(void);

enum e_event
{
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

enum e_mouse
{
	MOVE = 0,
	LEFT_CLICK = 1,
	RIGHT_CLICK = 2,
	MIDDLE_CLICK = 3,
	SCROLL_UP = 4,
	SCROLL_DOWN = 5
};

enum e_projection
{
	PROJ_PARALLEL,
	PROJ_ISOMETRIC
};

enum e_zoom
{
	ZOOM_IN = 1,
	ZOOM_OUT = -1
};

int		key_handler(int key, void *param);
int		mouse_handler(int button, int x, int y, t_prog *prog);
int		mouse_handler_down(int button, int x, int y, t_prog *prog);
int		mouse_handler_move(int x, int y, t_prog *prog);
int		mouse_handler_up(int button, int x, int y, t_prog *prog);
void	hook_all(t_prog *prog);

void	validate_line(char *line);

void	parse(char *filename, t_fdf_map *map);

void	init_req(t_prog *prog);
void	init_img(t_mlx *mlx);

# define SPACING 77
# define DO_SWAP 1
# define NO_SWAP 0

int		get_ordinate(int ordinate, t_fdf *fdf);
int		get_abscissa(int abscissa, t_fdf *fdf);
int		get_altitude(int altitude, t_fdf *fdf);

void	my_mlx_pixel_put(t_img *data, int x, int y, int color);
int		draw_debug_line(t_pt *point0, t_pt *point1, t_fdf *fdf, t_img *image);
void	draw(t_mlx *mlx, t_fdf *fdf);

#endif
