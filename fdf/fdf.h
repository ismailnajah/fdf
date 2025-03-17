/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:27:36 by inajah            #+#    #+#             */
/*   Updated: 2025/03/17 14:14:44 by inajah           ###   ########.fr       */
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
# include <stdbool.h>
# include <libgen.h>
# include "libft/libft.h"
# include "mlx.h"

# define ERR_FILE -1
# define ERR_MAP -2
# define ERR_PARSE -3
# define ERR_MALLOC -4
# define ERR_EMPTY_FILE -5
# define ERR_FILE_EXTENSION -6
# define ERR_IS_DIR -7

# define PI 3.14159265358979311600
# define EPSI 2

# define MAX_ZOOM 5000
# define MIN_ZOOM 200

# define ANGLE_STEP 1
# define OFFSET_STEP 1
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
};

//steps
enum
{
	X_OFF_STEP = 10,
	Y_OFF_STEP = 10,
	Z_OFF_STEP = 1,
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
	KEY_LECLICK = 1,
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
	DEFAULT_Z_OFF = 40,
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
	bool	focused;
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
	DOT_FACT,
	OPTION_COUNT,
};

typedef struct s_camera
{
	t_text_field	*field;
	float			option[OPTION_COUNT];
}	t_camera;

typedef struct s_mouse
{
	int	x;
	int	y;
	bool lepressed;
	bool right_pressed;
}	t_mouse;

typedef struct s_color_option
{
	t_point			*hue;
	t_point			*sat;
	bool			focused;
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
	t_mouse			*mouse;
	int				global_mode;
	int				tf_cursor;
}	t_vars;

//vars.c
int				is_vars_changed(t_vars *vars);
int				vars_free(t_vars *vars);
int				vars_init(t_vars *vars, char *map_path);

//label.c
void			label_draw(t_vars *vars);
void			label(t_vars *vars, int x, int y, char *text);
char			**labels_init(void);

//mouse.c
t_mouse			*mouse_init(void);
void	mouse_update_position(t_vars *vars, int x, int y);

//text_field.c
t_text_field	*text_field_init(t_camera *c);
void			text_field_focused(t_vars *vars, int mouse_x, int mouse_y);
int				text_field_event(int key, t_vars *vars);
int				text_field_sync_value(t_camera *c);

//text_field_draw.c
void			text_field_draw(t_vars *vars);

//color.c
int				create_trgb(int t, int r, int g, int b);
int				get_t(int trgb);
int				get_r(int trgb);
int				get_g(int trgb);
int				get_b(int trgb);

//color_picker
t_color_picker	*color_picker_init(int x, int y);
void			color_picker_draw(t_image *img, t_color_picker *cp);
void			border_draw(t_image *img, t_point a, int w, int h);
void			*color_picker_free(t_color_picker *cp);

//color_option.c
void			*color_option_free(t_color_option *opt);
t_color_option	*color_option_init(t_color_picker *cp);
void			color_option_draw(t_image *img, t_point p, int w);

//color_utils.c
int				color_picker_focused(t_color_picker *cp, int x, int y);
unsigned int	next_color(unsigned int color);
unsigned int	color_lerp(unsigned int c1, unsigned int c2, float t);
void			color_option_focused(t_vars *vars, int x, int y);
unsigned int	color_parse(char *color_str);

//draw.c
void			draw_pixel(t_image *img, int x, int y, int color);
void			draw_main_view(t_vars *vars);
void			draw_line(t_image *img, t_point a, t_point b, int fact);

//draw_utils.c
unsigned int	get_point_color(t_vars *vars, t_point *p);
float			point_distance(t_point a, t_point b);
int				in_image(t_image *img, t_point a);

//handle_event.c
int				on_keydown(int keycode, t_vars *vars);
int				on_destroy(t_vars *vars);
int				on_mouse_event(int keycode, int x, int y, t_vars *vars);
int				on_mouse_up(int button, int x, int y, t_vars *vars);
int				on_mouse_move(int x, int y, t_vars *vars);

//map.c
t_map			*map_init(int w, int h);
void			*map_free(t_map *map);
void			get_min_max_z(t_map *map, int *min, int *max);
int				map_realloc_points(t_map *map);
void			normalize_z(t_map *map);

//parse_map.c
void			*map_free(t_map *map);
t_map			*map_init(int w, int h);
t_map			*get_map_from_file(char *path);
void			get_min_max_z(t_map *map, int *min, int *max);

//image.c
void			*image_free(void *mlx, t_image *img);
t_image			*image_init(void *mlx, int width, int height);
void			image_clear(t_image *img, unsigned int color);
void			*layout_free(void *mlx, t_layout *layout);
t_layout		*layout_init(void *mlx);
void			layout_set_image_focused(t_layout *layout, int x, int y);
void			layout_reset_image_focused(t_layout *layout);

//math.c
void			angle_change(float *angle, int direction);
void			rotate_xyz_point(t_point *p, t_point *proj, t_camera *c);

//camera.c
t_camera		*camera_init(void);
void			*camera_free(t_camera *c);
t_camera		camera_of_view(int view, t_camera *old_s);
t_camera		camera_default(void);
void	camera_update_zoom(t_camera *camera, t_mouse *mouse, int scale_step);
void			camera_update(t_camera *s, t_camera *e);

//camera_utils.c
void			camera_angle_update(float *angle, int direction);
void			camera_offset_update(float *s, float *e);

//point.c
t_point			*point_init(float x, float y, float z, unsigned int color);
int				point_sort(t_point *a, t_point *b);
void			point_scale(t_point *a, t_point *p, t_camera *c);
void			point_copy(t_point	*dst, t_point *src);

//utils.c
void			view_change(int state, t_vars *vars);
unsigned int	color_lerp(unsigned int c1, unsigned int c2, float t);
unsigned int	hex_to_int(char *hex);
int				print_error(int err, char *path);
int				is_valid_file(char *path);

//cube.c
void			draw_cube_view(t_image *img, t_vars *vars);
int				is_cube_clicked(int x, int y, t_vars *vars);

//rect.c
t_rect			*rect_init(int x, int y, int w, int h);
void			rect_draw(t_image *img, t_rect *rec, unsigned int c);
int				is_inside_rect(t_rect *rec, int x, int y);
void			border_draw(t_image *img, t_point a, int w, int h);

//circle.c
void			circle_draw(t_image *img, t_point center);

#endif
