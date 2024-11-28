/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:27:36 by inajah            #+#    #+#             */
/*   Updated: 2024/11/28 18:16:21 by inajah           ###   ########.fr       */
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
# include "mlx.h"

# define ERR_FILE -1
# define ERR_MAP -2
# define ERR_PARSE -3
# define ERR_MALLOC -4
# define ERR_EMPTY_FILE -5

# define PI 3.14159265358979311600
# define EPSI 2

# define MAX_ZOOM 8000
# define MIN_ZOOM 200

# define ANGLE_STEP 1
# define OFFSET_STEP 10
# define Z_STEP 0.05f

# define FACT 120

# define CP_HUE 1
# define CP_SAT 2
# define LOW_P_OPT 1
# define HIGH_P_OPT 2

# define C_WHITE 0x00FFFFFF
# define C_RED	 0x00FF0000
# define C_GREEN 0x0000FF00
# define C_BLUE  0x000000FF
# define C_GREY  0x00181818
# define C_BLACK 0x00000000

//draw settings
enum
{
	WIN_W = 16 * FACT,
	WIN_H = 9 * FACT,
	MAIN_W = WIN_W - WIN_W / 5,
	MAIN_H = WIN_H,
	CUBE_W = WIN_W / 20,
	CUBE_H = CUBE_W,
	MENU_W = WIN_W / 5,
	MENU_H = WIN_H,
	COLOR_W = 50,
	LP_COLOR_X = MENU_W / 2,
	LP_COLOR_Y = MENU_H / 2 - COLOR_W,
	HP_COLOR_Y = MENU_H / 2 + 10,
	TEXT_FIELD_W = MENU_W / 5,
	TEXT_FIELD_H = 30,
	TEXT_FIELD_MAX_CHAR = 6,
	SCALE_STEP = (MAX_ZOOM - MIN_ZOOM) / 40,
};

//modes like vim
enum
{
	NORMAL,
	INSERT,
};

// animation state
enum
{
	STOP_ANIMATION,
	START_ANIMATION,
	UPDATE_ANIMATION,
	RESET_ANIMATION,
};

//keys codes
enum
{
	KEY_ENTER = 65293,
	KEY_BACK_SPACE = 65288,
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

//default values
enum
{
	DEFAULT_ANGLE_X = 35,
	DEFAULT_ANGLE_Y = 45,
	DEFAULT_ANGLE_Z = -60,
	DEFAULT_SCALE = 300,
	DEFAULT_X_OFF = (MAIN_W / 2),
	DEFAULT_Y_OFF = (MAIN_H / 2),
	DEFAULT_Z_OFF = 1,
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
	int		w;
	int		h;
	float	max_z;
	float	min_z;
	t_point	*points;
}	t_map;

typedef struct s_layout
{
	t_image	*main;
	t_image	*cube_view;
	t_image	*menu;
}	t_layout;

typedef struct s_text_field
{
	int		x;
	int		y;
	int		w;
	int		h;
	int		focused;
	char	text[TEXT_FIELD_MAX_CHAR];
}	t_text_field;

typedef struct s_rectangle
{
	int	x;
	int	y;
	int	w;
	int	h;
}	t_rect;

typedef struct s_color_picker
{
	int		x;
	int		y;
	int		focused;
	t_rect	*hue;
	t_rect	*sat;
	t_point	*hue_cursor;
	t_point	*sat_cursor;

}	t_color_picker;

enum
{
	ANGLE_X,
	ANGLE_Y,
	ANGLE_Z,
	X_OFF,
	Y_OFF,
	Z_OFF,
	SCALE,
	OPTION_COUNT,
};

typedef struct s_camera
{
	t_text_field	*field;
	float			option[OPTION_COUNT];
}	t_camera;

typedef struct s_color_option
{
	t_point			*hue;
	t_point			*sat;
	int				focused;
	unsigned int	color;
}	t_color_option;

typedef struct s_vars
{
	void			*mlx;
	void			*win;
	t_map			*map;
	t_layout		*layout;
	t_point			*cube;
	t_camera		*camera;
	t_color_picker	*color_picker;
	t_color_option	*low_p;
	t_color_option	*high_p;
	char			**labels;
	int				mouse_x;
	int				mouse_y;
	int				global_mode;
	int				tf_cursor;
}	t_vars;

//ft_vars.c
int				ft_is_vars_changed(t_vars *vars);
int				ft_vars_free(t_vars *vars);
int				ft_vars_init(t_vars *vars, char *map_path);

//ft_label.c
void			ft_label_draw(t_vars *vars);
void			ft_label(t_vars *vars, int x, int y, char *text);
char			**ft_labels_init(void);

//ft_text_field.c
t_text_field	*ft_text_field_init(t_camera *c);
void			ft_text_field_focused(t_vars *vars, int mouse_x, int mouse_y);
int				ft_text_field_event(int key, t_vars *vars);
void			ft_camera_update_value(t_camera *c, int i);
int				ft_text_field_sync_value(t_camera *c);

//ft_text_field_draw.c
void			ft_text_field_draw(t_vars *vars);

//ft_color.c
int				create_trgb(int t, int r, int g, int b);
int				get_t(int trgb);
int				get_r(int trgb);
int				get_g(int trgb);
int				get_b(int trgb);

//ft_color_picker
t_color_picker	*ft_color_picker_init(int x, int y);
void			ft_color_picker_draw(t_image *img, t_color_picker *cp);
void			ft_border_draw(t_image *img, t_point a, int w, int h);
void			*ft_color_picker_free(t_color_picker *cp);

//ft_color_option.c
void			*ft_color_option_free(t_color_option *opt);
t_color_option	*ft_color_option_init(t_color_picker *cp);
void			ft_color_option_draw(t_image *img, t_point p, int w);

//ft_color_utils.c
int				ft_color_picker_focused(t_color_picker *cp, int x, int y);
unsigned int	next_color(unsigned int color);
unsigned int	ft_color_lerp(unsigned int c1, unsigned int c2, float t);
void			ft_color_option_focused(t_vars *vars, int x, int y);
unsigned int	ft_color_parse(char *color_str);

//ft_draw.c
void			ft_draw_pixel(t_image *img, int x, int y, int color);
void			ft_draw_main_view(t_vars *vars);
void			ft_draw_line(t_image *img, t_point a, t_point b);

//ft_draw_utils.c
unsigned int	ft_get_point_color(t_vars *vars, t_point *p);
float			ft_point_distance(t_point a, t_point b);
int				ft_in_image(t_image *img, t_point a);
void			ft_scale_z(t_map *map, float z_off);

//ft_handle_event.c
int				ft_on_keydown(int keycode, t_vars *vars);
int				ft_on_destroy(t_vars *vars);
int				ft_on_mouse_event(int keycode, int x, int y, t_vars *vars);
int				ft_on_mouse_up(int button, int x, int y, t_vars *vars);
int				ft_on_mouse_move(int x, int y, t_vars *vars);

//ft_map.c
t_map			*ft_map_init(int w, int h);
void			*ft_map_free(t_map *map);
void			ft_get_min_max_z(t_map *map, int *min, int *max);
int				ft_map_realloc_points(t_map *map);

//ft_parse_map.c
void			ft_map_debug(t_map *map);
void			*ft_map_free(t_map *map);
t_map			*ft_map_init(int w, int h);
t_map			*ft_get_map_from_file(char *path);
void			ft_get_min_max_z(t_map *map, int *min, int *max);
void			*ft_words_free(char **words);

//ft_image.c
void			*ft_image_free(void *mlx, t_image *img);
t_image			*ft_image_init(void *mlx, int width, int height);
void			ft_image_clear(t_image *img, unsigned int color);
void			*ft_layout_free(void *mlx, t_layout *layout);
t_layout		*ft_layout_init(void *mlx);

//ft_math.c
float			ft_fmod(float value, float div);
void			ft_angle_change(float *angle, int direction);
void			ft_rotate_xyz_point(t_point *p, t_point *proj, t_camera *s);

//ft_camera.c
t_camera		*ft_camera_init(void);
void			*ft_camera_free(t_camera *c);
t_camera		ft_camera_of_view(int view, t_camera *old_s);
t_camera		ft_camera_default(void);
void			ft_camera_animate(t_camera *s, t_camera *e);

//ft_point.c
t_point			*ft_point_init(float x, float y, float z, unsigned int color);
int				ft_point_sort(t_point *a, t_point *b);
void			ft_point_scale(t_point *a, t_point *p, t_camera *c);
void			ft_point_copy(t_point	*dst, t_point *src);

//ft_utils.c
void			ft_view_change(int state, t_vars *vars);
unsigned int	ft_color_lerp(unsigned int c1, unsigned int c2, float t);
unsigned int	ft_hex_to_int(char *hex);
void			ft_normalize_z(t_map *map);
int				ft_print_error(int err);

//ft_cube.c
void			ft_draw_cube_view(t_image *img, t_vars *vars);
int				ft_is_cube_clicked(int x, int y, t_vars *vars);

//ft_rect.c
t_rect			*ft_rect_init(int x, int y, int w, int h);
void			ft_rect_draw(t_image *img, t_rect *rec, unsigned int c);
int				ft_is_inside_rect(t_rect *rec, int x, int y);
void			ft_border_draw(t_image *img, t_point a, int w, int h);

//ft_circle.c
void			ft_circle_draw(t_image *img, t_point center);

#endif
