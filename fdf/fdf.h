/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:27:36 by inajah            #+#    #+#             */
/*   Updated: 2024/11/20 14:09:38 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <limits.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include "libft/libft.h"

# define MAX_ZOOM  8000
# define MIN_ZOOM 200

# define START_ANIMATION 1
# define STOP_ANIMATION 0

# define ANGLE_STEP 1
# define SCALE_STEP (MAX_ZOOM - MIN_ZOOM) / 40
# define OFFSET_STEP 10
# define Z_OFFSET_STEP 0.05f

# define FACT 120
# define WIN_W (16 * FACT)
# define WIN_H (9 * FACT)

# define MAIN_W (WIN_W * 1)
# define MAIN_H WIN_H

# define TOP_W (WIN_W - MAIN_W)
# define TOP_H (WIN_H / 2)

# define SIDE_W (WIN_W * 0.05)
# define SIDE_H (WIN_W * 0.05)

# define C_WHITE 0x00FFFFFF
# define C_RED	 0x55FF0000
# define C_GREEN 0x5500FF00
# define C_BLUE  0x550000FF
# define C_BLACK 0x00000000

//default settings
# define DEFAULT_ANGLE_X 58.0f
# define DEFAULT_ANGLE_Y 40.0f
# define DEFAULT_ANGLE_Z -22.0f
# define DEFAULT_SCALE 500
# define DEFAULT_X_OFF (MAIN_W / 2)
# define DEFAULT_Y_OFF (MAIN_H / 2)
# define DEFAULT_Z_OFF 1.0f



//keys codes
enum 
{
	KEY_ESC = 53,
	KEY_UP = 126,
	KEY_DOWN = 125,
	KEY_LEFT = 123,
	KEY_RIGHT = 124,
	KEY_W = 13,
	KEY_S = 1,
	KEY_A = 0,
	KEY_D = 2,
	KEY_E = 14,
	KEY_Q = 12,
	KEY_V = 9,
	KEY_PLUS = 24,
	KEY_MINUS = 27,
	KEY_SPACE = 49,
	KEY_SCROLL_UP = 4,
	KEY_SCROLL_DOWN = 5,
	KEY_LEFT_CLICK = 1,
	KEY_RIGHT_CLICK = 2,
};

//events codes
enum 
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

//views
enum
{
	FRONT_VIEW = 1,
	SIDE_VIEW,
	TOP_VIEW,
	DEFAULT_VIEW,
};

typedef struct s_image
{
	void	*data;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		w;
	int		h;
}	t_image;

typedef struct s_point
{
	float			x;
	float			y;
	float			z;
	unsigned int	color;
}	t_point;

typedef struct s_map
{
	int	w;
	int	h;
	t_point	*points;
}	t_map;



typedef struct s_layout
{
	t_image	*main; // the main image where the fdf is rendered
	t_image	*top;  // top view of the fdf 
	t_image	*side; // side view of the fdf
}	t_layout;

typedef	struct s_setting
{
	float	angleX;
	float	angleY;
	float	angleZ;
	int		scale;
	int		x_off;
	int		y_off;
	float	z_off;
}	t_setting;

typedef struct s_vars
{
	void		*mlx;
	void		*win;
	t_map		*map;
	t_layout	*layout;
	t_setting	*setting;
	t_point		*cube;
	int			mouse_x;
	int			mouse_y;
}	t_vars;

typedef struct	s_matrix
{
	int	w;
	int	h;
	float	*values;
}	t_matrix;

int	create_trgb(int t, int r, int g, int b);
int	get_t(int trgb);
int	get_r(int trgb);
int	get_g(int trgb);
int	get_b(int trgb);

int ft_fill_image(t_image *img, int w, int h, size_t color);

void	ft_debug_map(t_map *map);
void	*ft_free_map(t_map *map);
t_map	*ft_init_map(int w, int h);
t_map	*ft_get_map_from_file(char *path);


void	*ft_matrix_free(t_matrix *mat);
t_matrix	*ft_matrix_init(int w, int h);
void	ft_matrix_point_mul(t_matrix *mat, t_point *p, t_point *out);
void	ft_matrix_rotateX(t_matrix *mat, float angle);
void	ft_matrix_rotateY(t_matrix *mat, float angle);
void	ft_matrix_rotateZ(t_matrix *mat, float angle);



#endif
