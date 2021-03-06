/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 11:09:46 by thakala           #+#    #+#             */
/*   Updated: 2022/04/05 21:54:22 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h> // man 2 open
# include <unistd.h> // man 2 read; man 2 write; man 2 close
# include <stdlib.h> // man 3 malloc; man 3 free; man 3 exit
# include <math.h> // man 3 math

# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"

# define WIN_HEIGHT 960
# define WIN_WIDTH 1280
# define WIN_NAME "FdF-thakala-0"

typedef struct s_point
{
	int		row;
	int		col;
}	t_pt;

typedef struct s_minmaxdir
{
	int		min;
	int		max;
}	t_mmd;

typedef struct s_segment
{
	t_pt	*b;
	t_pt	*e;
}	t_segm;

typedef struct s_double_coordinate
{
	double	row;
	double	col;
}	t_db_pt;

typedef struct s_row
{
	int		*line;
	int		point_count;
	int		size;
}	t_row;

typedef struct s_map
{
	t_row		*lines;
	int			line_count;
	int			size;
	int			max_point_count;
	t_mmd		height;
}	t_fdf_map;

typedef struct s_mouse
{
	t_pt	prev;
	t_pt	curr;
	t_pt	diff;
	char	isdown;
}	t_mse;

typedef struct s_key_states
{
	int		cmd_toggled;
}	t_key;

# define HEIGHT_ADDITION (double)5.5

typedef struct s_fdf
{
	t_pt		origin;
	t_pt		offset;
	double		height;
	int			zoom;
	int			proj;
	int			colour_theme;
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
	t_key	*key;
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
	KEY_C_OLOUR = 8,
	KEY_P_ROJECTION = 35,
	KEY_ESC = 53,
	KEY_L_CMD = 259,
	KEY_R_CMD = 260
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
	PROJ_PARALLEL = 0,
	PROJ_ISOMETRIC = 30,
	DIFF_ISO_MIL = 15,
	PROJ_MILITARY = 45
};

enum e_zoom
{
	ZOOM_IN = 1,
	ZOOM_OUT = -1
};

void	pan(t_prog *prog);
int		zoomer(int dir, int zoom);
void	offsetter(t_pt *mse, t_prog *prog, int prev_zoom);
void	stick_zoom(unsigned int *zoom);

int		key_handler(int key, t_prog *param);
int		mouse_handler(int button, int x, int y, t_prog *prog);
int		mouse_handler_down(int button, int x, int y, t_prog *prog);
int		mouse_handler_move(int x, int y, t_prog *prog);
int		mouse_handler_up(int button, int x, int y, t_prog *prog);
void	rotate_colour_theme(t_prog *prog);
void	rotate_projection(t_prog *prog);
void	hook_all(t_prog *prog);

void	line_lengths_equal(t_fdf_map *map);
void	parse(char *filename, t_fdf_map *map);

double	max(double d0, double d1);
int		abs_max(int i0, int i1);

void	init_map(t_fdf_map *map);
void	init_req(t_prog *prog);
void	init_origin(t_fdf *fdf);
void	init_offset(t_fdf *fdf);
void	init_img(t_mlx *mlx, t_fdf *fdf);

# define SPACING 2
# define DO_SWAP 1
# define NO_SWAP 0

# define POINT_0 0
# define POINT_1 1

# define LOWEST ((double)0.4242424242424242)
# define HIGHEST ((double)1.0)

enum e_colour_theme
{
	RED = 16,
	GREEN = 8,
	BLUE = 0
};

# define INT_MAX 2147483647
# define INT_MIN -2147483648l

int		get_colour(double percentage, t_segm *pts, t_fdf *fdf);

int		get_ordinate(int ordinate, t_fdf *fdf);
int		get_abscissa(int abscissa, t_fdf *fdf);
int		get_altitude(int altitude, t_fdf *fdf);

void	my_mlx_pixel_put(t_img *data, int x, int y, int color);
int		compare_heights(t_pt *point0, t_pt *point1, t_fdf *fdf);
void	swap_points(t_pt **point0, t_pt **point1, int condition);
int		in_range(int lowest, int value, int upto);
void	project(t_pt *dst, t_pt *src, t_fdf *fdf);
void	draw(t_mlx *mlx, t_fdf *fdf);

#endif
