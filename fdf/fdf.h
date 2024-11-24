/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:27:36 by inajah            #+#    #+#             */
/*   Updated: 2024/11/24 08:06:15 by inajah           ###   ########.fr       */
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
#include "mlx.h"


# define PI 3.14159265358979311600

# define MAX_ZOOM 8000
# define MIN_ZOOM 200

# define ANGLE_STEP 1
# define SCALE_STEP (MAX_ZOOM - MIN_ZOOM) / 40
# define OFFSET_STEP 10
# define Z_STEP 0.05f

# define FACT 70
# define WIN_W (16 * FACT)
# define WIN_H (9 * FACT)

# define MAIN_W (WIN_W * 1)
# define MAIN_H WIN_H

# define CUBE_W (WIN_W * 0.05)
# define CUBE_H (WIN_W * 0.05)

# define C_WHITE 0x00FFFFFF
# define C_RED	 0x55FF0000
# define C_GREEN 0x5500FF00
# define C_BLUE  0x550000FF
# define C_BLACK 0x00000000

//default settings
# define DEFAULT_ANGLE_X 35.0f
# define DEFAULT_ANGLE_Y 45.0f
# define DEFAULT_ANGLE_Z -60.0f
# define DEFAULT_SCALE 500
# define DEFAULT_X_OFF (MAIN_W / 2)
# define DEFAULT_Y_OFF (MAIN_H / 2)
# define DEFAULT_Z_OFF 1.0f

// animation state
enum
{
	STOP_ANIMATION,
	START_ANIMATION,
	UPDATE_ANIMATION,
	RESET_ANIMATION,
};

//keys codes
#ifdef __linux__
enum 
{
	KEY_ESC = 65307,
	KEY_UP = 65362,
	KEY_DOWN = 65364,
	KEY_LEFT = 65361,
	KEY_RIGHT = 65363,
	KEY_W = 119,
	KEY_S = 115,
	KEY_A = 97,
	KEY_D = 100,
	KEY_E = 101,
	KEY_Q = 113,
	KEY_V = 118,
	KEY_PLUS = 61,
	KEY_MINUS = 45,
	KEY_SPACE = 32,
	KEY_SCROLL_UP = 4,
	KEY_SCROLL_DOWN = 5,
	KEY_LEFT_CLICK = 1,
	KEY_RIGHT_CLICK = 2,
};

#else

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

#endif

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
	t_image	*cube_view; // the cube image in top right
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

//main.c
int	ft_vars_free(t_vars *vars);

//ft_color.c
int	create_trgb(int t, int r, int g, int b);
int	get_t(int trgb);
int	get_r(int trgb);
int	get_g(int trgb);
int	get_b(int trgb);

//ft_draw.c
void	ft_draw_pixel(t_image *img, int x, int y, int color);
void	ft_draw_cell(t_image *img, t_vars *vars, int i, int j);
void	ft_draw_main_view(t_vars *vars);
void	ft_draw_line(t_image *img, t_point a, t_point b);


//ft_handle_event.c
int	ft_on_keydown(int keycode, t_vars *vars);
int	ft_on_destroy(t_vars *vars);
int	ft_on_mouse_event(int keycode, int x, int y, t_vars *vars);

//ft_parse_map.c
void	ft_map_debug(t_map *map);
void	*ft_map_free(t_map *map);
t_map	*ft_map_init(int w, int h);
t_map	*ft_get_map_from_file(char *path);
void	ft_get_min_max_z(t_map *map, int *min, int *max);

//ft_image.c
void			*ft_image_free(void *mlx, t_image *img);
t_image			*ft_image_init(void *mlx, int width, int height);
void			ft_image_clear(t_image *img);
void			*ft_layout_free(void *mlx, t_layout *layout);
t_layout		*ft_layout_init(void *mlx);

//ft_math.c
float			ft_fmod(float value, float div);
void			ft_angle_change(float *angle, int direction);
void			ft_rotate_xyz_point(t_point *p, t_point *projected, t_setting *s);

//ft_setting.c
t_setting		*ft_setting_init(void);
t_setting		ft_setting_of_view(int view, t_setting *old_s);
t_setting		ft_setting_default(void);
void			ft_setting_animate(t_setting *s, t_setting *e);
void			print_setting(t_setting *s);

//ft_point.c
void			ft_view_change(int state, t_vars *vars);
int				ft_point_sort(t_point *a, t_point *b);
void			ft_point_scale(t_point *a, t_point *p, t_setting *s);

//ft_utils.c
unsigned int	ft_color_lerp(unsigned int c1, unsigned int c2, float t);
void			ft_scale_z(t_map *map, float z_off);
unsigned int	ft_hex_to_int(char *hex);
void			ft_normalize_z(t_map *map);

//ft_cube.c
void			ft_draw_cube_view(t_image *img, t_vars *vars);
int				ft_is_cube_clicked(int x, int y, t_vars *vars);

#endif
