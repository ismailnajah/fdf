/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 21:13:24 by inajah            #+#    #+#             */
/*   Updated: 2024/11/21 18:22:35 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include <stdio.h>


void my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char *dst;

	if (x < 0 || y < 0 || x >= img->w || y >= img->h)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*) dst = color;
}

void	*ft_image_free(void *mlx, t_image *img)
{
	if (!img)
		return (NULL);
	mlx_destroy_image(mlx, img->data);
	free(img);
	return (NULL);
}

t_image	*ft_init_image(void *mlx, int width, int height)
{
	t_image *img;

	img = (t_image*)malloc(sizeof(t_image));
	if (!img)
		return (NULL);
	img->data = mlx_new_image(mlx, width, height);
	if (!img->data)
		return (ft_abort(img));
	img->addr = mlx_get_data_addr(img->data, &img->bits_per_pixel, &img->line_length, &img->endian);
	if (!img->addr)
		return (ft_image_free(mlx, img));
	img->w = width;
	img->h = height;
	return (img);
}

void* ft_layout_free(void *mlx, t_layout *layout)
{
	if (!layout)
		return (NULL);
	ft_image_free(mlx, layout->main);
	ft_image_free(mlx, layout->cube_view);
	free(layout);
	return (NULL);
}

t_layout *ft_layout_init(void* mlx)
{
	t_layout *layout;

	layout = (t_layout*)malloc(sizeof(t_layout));
	if(!layout)
		return (NULL);
	layout->main = ft_init_image(mlx, MAIN_W, MAIN_H);
	if (!layout->main)
		return (ft_layout_free(mlx, layout));
	layout->cube_view = ft_init_image(mlx, CUBE_W, CUBE_H);
	if (!layout->cube_view)
		return (ft_layout_free(mlx, layout));
	return (layout);
}

float	ft_clamp(float value, float min, float max)
{
	if (value <= min || value >= max)
		return (0.0f);
	return (value);
}

void	ft_reset_setting(int state, t_setting *s)
{
	static int start;

	if (state)
		start = 1;
	if (!start)
		return ;
	if (s->angleX != DEFAULT_ANGLE_X)
		s->angleX += (1 - 2 * (s->angleX > DEFAULT_ANGLE_X)) * ANGLE_STEP;
	if (s->angleY != DEFAULT_ANGLE_Y)
		s->angleY += (1 - 2 * (s->angleY > DEFAULT_ANGLE_Y)) * ANGLE_STEP;
	if (s->angleZ != DEFAULT_ANGLE_Z)
		s->angleZ += (1 - 2 * (s->angleZ > DEFAULT_ANGLE_Z)) * ANGLE_STEP;
	if (s->scale != DEFAULT_SCALE)
		s->scale += (1 - 2 * (s->scale > DEFAULT_SCALE)) * SCALE_STEP;
	if (s->x_off != DEFAULT_X_OFF)
		s->x_off += (1 - 2 * (s->x_off > DEFAULT_X_OFF)) * OFFSET_STEP;
	if (s->y_off != DEFAULT_Y_OFF)
		s->y_off += (1 - 2 * (s->y_off > DEFAULT_Y_OFF)) * OFFSET_STEP;
	if (s->z_off != DEFAULT_Z_OFF)
		s->z_off += (1 - 2 * (s->z_off > DEFAULT_Z_OFF)) * Z_OFFSET_STEP;
	if (s->angleX == DEFAULT_ANGLE_X && s->angleY == DEFAULT_ANGLE_Y
			&& s->angleZ == DEFAULT_ANGLE_Z && s->scale == DEFAULT_SCALE
			&& s->x_off == DEFAULT_X_OFF && s->y_off == DEFAULT_Y_OFF
			&& s->z_off == DEFAULT_Z_OFF)
		start = 0;
}

void	print_setting(t_setting *s)
{
	printf("[angleX: %.2f | angleY: %.2f | angleZ: %.2f | scale: %d | x_off: %d | y_off: %d | z_off: %.2f]\n", s->angleX, s->angleY, s->angleZ, s->scale, s->x_off, s->y_off, s->z_off);
}

void	ft_scale_z(t_map *map, float z_off)
{
	int		i;

	i = 0;
	while (i < map->w * map->h && z_off != 0.0f)
	{
		map->points[i].z /= z_off;
		i++;
	}
}

int ft_on_keydown(int keycode, t_vars *vars)
{
	if (keycode == KEY_ESC)
	{
		ft_vars_free(vars);
		exit(0);
	}
	if (keycode == KEY_A)
		vars->setting->angleX = ft_clamp(vars->setting->angleX + ANGLE_STEP, -360.0f, 360.0f);
	if (keycode == KEY_D)
		vars->setting->angleX = ft_clamp(vars->setting->angleX - ANGLE_STEP, -360.0f, 360.0f);
	if (keycode == KEY_S)
		vars->setting->angleY = ft_clamp(vars->setting->angleY + ANGLE_STEP, -360.0f, 360.0f);
	if (keycode == KEY_W)
		vars->setting->angleY = ft_clamp(vars->setting->angleY - ANGLE_STEP, -360.0f, 360.0f);
	if (keycode == KEY_Q)
		vars->setting->angleZ = ft_clamp(vars->setting->angleZ + ANGLE_STEP, -360.0f, 360.0f);
	if (keycode == KEY_E)
		vars->setting->angleZ = ft_clamp(vars->setting->angleZ - ANGLE_STEP, -360.0f, 360.0f);
	if (keycode == KEY_UP)
		vars->setting->y_off -= OFFSET_STEP;
	if (keycode == KEY_DOWN)
		vars->setting->y_off += OFFSET_STEP;
	if (keycode == KEY_LEFT)
		vars->setting->x_off -= OFFSET_STEP;
	if (keycode == KEY_RIGHT)
		vars->setting->x_off += OFFSET_STEP;
	if (keycode == KEY_PLUS)
		ft_scale_z(vars->map, 1 - Z_OFFSET_STEP);
	if (keycode == KEY_MINUS)
		ft_scale_z(vars->map, 1 + Z_OFFSET_STEP);
	if (keycode == KEY_V)
		print_setting(vars->setting);
	if (keycode == KEY_SPACE)
		ft_reset_setting(1, vars->setting);
	//printf("keycode: %d\n", keycode);
	return (0);
}

int ft_on_destroy(t_vars *vars)
{
	ft_vars_free(vars);
	ft_printf("[ INFO  ] Window Closed\n");
	exit(0);
	return (0);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	get_t(int trgb)
{
	return ((trgb >> 24) & 0xFF);
}

int	get_r(int trgb)
{
	return ((trgb >> 16) & 0xFF);
}

int	get_g(int trgb)
{
	return ((trgb >> 8) & 0xFF);
}

int	get_b(int trgb)
{
	return (trgb & 0xFF);
}


unsigned int ft_color_lerp(unsigned int c1, unsigned int c2, float t)
{
	int r;
	int g;
	int b;

	r = get_r(c1) + t * (get_r(c2) - get_r(c1));
	g = get_g(c1) + t * (get_g(c2) - get_g(c1));
	b = get_b(c1) + t * (get_b(c2) - get_b(c1));
	return create_trgb(0, r, g, b);
}

void	ft_swap_point(t_point *a, t_point *b)
{
	float			tmp;
	unsigned int	c;

	tmp = b->x;
	b->x = a->x;
	a->x = tmp;
	tmp = b->y;
	b->y = a->y;
	a->y = tmp;
	tmp = b->z;
	b->z = a->z;
	a->z = tmp;
	c = b->color;
	b->color = a->color;
	a->color = c;
}

int	ft_sort_point(t_point *a, t_point *b)
{
	if (fabs(a->x - b->x) < fabs(a->y - b->y))
	{
		if (a->y > b->y)
			ft_swap_point(a, b);	
		return (1);
	}
	else if (a->x > b->x)
		ft_swap_point(a,b);
	return (0);
}

void ft_draw_line(t_image *img, t_point a, t_point b)
{
	float y;
	float x;

	if (ft_sort_point(&a, &b))
	{
		y = a.y;
		while (y <= b.y && a.y != b.y)
		{
			x = a.x + (y - a.y) * ((b.x - a.x) / (b.y - a.y));
			my_mlx_pixel_put(img, x, y, ft_color_lerp(a.color, b.color, (float)y / b.y));
			y += 1;
		}
	} 
	else
	{
		x = a.x;
		while (x <= b.x && a.x != b.x)
		{
			y = a.y + (x - a.x) * ((b.y - a.y) / (b.x - a.x));
			my_mlx_pixel_put(img, x, y, ft_color_lerp(a.color, b.color, (float)x / b.x));
			x += 1;
		}
	}
}

void	ft_scale_point(t_point *a, t_point *p, t_setting *s)
{
	a->x = p->x * s->scale + s->x_off;
	a->y = p->y * s->scale + s->y_off;
	a->color = p->color;
}

void	ft_draw_projected_cell(t_image *img, t_map *map, t_setting *s, int i, int j)
{
	t_point	a;
	t_point b;
	t_point proj;	

	ft_rotateXYZ_point(map->points + (j * map->w + i), &proj, s);	
	ft_scale_point(&a, &proj, s);
	if (i + 1 < map->w)
	{
		ft_rotateXYZ_point(map->points + (j * map->w + i + 1), &proj, s);	
		ft_scale_point(&b, &proj, s);
		ft_draw_line(img, a, b);
	}
	if (j + 1 < map->h)
	{
		ft_rotateXYZ_point(map->points + ((j + 1) * map->w + i), &proj, s);	
		ft_scale_point(&b, &proj, s);
		ft_draw_line(img, a, b);
	}
}

void	ft_draw_main_view(t_image *img, t_map *map, t_setting *s)
{
	int	i;
	int j;
	
	j = 0;
	while (j < map->h)
	{
		i = 0;
		while (i < map->w)
		{

			ft_draw_projected_cell(img, map, s, i, j);
			i++;
		}
		j++;
	}
}

t_setting	*init_setting(void)
{
	t_setting	*s;

	s = (t_setting*)malloc(sizeof(t_setting));
	if (!s)
		return (NULL);
	s->angleX = DEFAULT_ANGLE_X;
	s->angleY = DEFAULT_ANGLE_Y;
	s->angleZ = DEFAULT_ANGLE_Z;
	s->scale = DEFAULT_SCALE;
	s->x_off = DEFAULT_X_OFF;
	s->y_off = DEFAULT_Y_OFF;
	s->z_off = DEFAULT_Z_OFF;
	return (s);
}

void	ft_draw_cube_view(t_image *img, t_vars *vars)
{
	t_point cube[8];
	t_setting *cube_setting;

	cube_setting = init_setting();

	cube[0].x = -0.5f;
	cube[0].y = 0.5f;
	cube[0].z = 0.5f;
	cube[1].x = 0.5f;
	cube[1].y = 0.5f;
	cube[1].z = 0.5f;
	cube[2].x = 0.5f;
	cube[2].y = 0.5f;
	cube[2].z = -0.5f;
	cube[3].x = -0.5f;
	cube[3].y = 0.5f;
	cube[3].z = -0.5f;
	cube[4].x = -0.5f;
	cube[4].y = -0.5f;
	cube[4].z = 0.5f;
	cube[5].x = 0.5f;
	cube[5].y = -0.5f;
	cube[5].z = 0.5f;
	cube[6].x = 0.5f;
	cube[6].y = -0.5f;
	cube[6].z = -0.5f;
	cube[7].x = -0.5f;
	cube[7].y = -0.5f;
	cube[7].z = -0.5f;

	for(int i=0; i< 8; i++)
	{
		ft_rotateXYZ_point(cube + i, vars->cube + i, cube_setting);
		vars->cube[i].x = vars->cube[i].x * img->w * 0.5 + img->w / 2;
		vars->cube[i].y = vars->cube[i].y * img->w * 0.5 + img->h / 2;
		vars->cube[i].color = C_WHITE;
	}
	// side view
	for(int i = 0; i < 4; i++)
	{
		ft_draw_line(img, vars->cube[i % 4], vars->cube[(i + 1) % 4]);
	}
	ft_draw_line(img, vars->cube[0], vars->cube[3]);
	ft_draw_line(img, vars->cube[0], vars->cube[4]);
	ft_draw_line(img, vars->cube[7], vars->cube[3]);
	ft_draw_line(img, vars->cube[4], vars->cube[7]);
	// top view
	ft_draw_line(img, vars->cube[4], vars->cube[5]);
	ft_draw_line(img, vars->cube[5], vars->cube[1]);
	free(cube_setting);
}

int	ft_is_cube_clicked(int x, int y, t_vars *vars)
{
	t_point *cube;

	if (x == -1 && y == -1)
		return (DEFAULT_VIEW);
	x = x - (WIN_W - vars->layout->cube_view->w);//the cube in top right corner.
	cube = vars->cube;
	if (cube[4].x < x && x < cube[1].x && cube[5].y < y && y < cube[0].y)
		return (TOP_VIEW);
	if (cube[7].x < x && x < cube[3].x && cube[0].y < y && y < cube[3].y)
		return (FRONT_VIEW);
	if (cube[3].x < x && x < cube[2].x && cube[0].y < y && y < cube[3].y)
		return (SIDE_VIEW);
	return (0); 
}

t_setting *ft_get_view_setting(int view, t_setting *old_s)
{
	t_setting	*s;

	s = init_setting();
	if (view == TOP_VIEW)
	{
		s->angleX = 0.0f;
		s->angleY = 0.0f;
		s->angleZ = 0.0f;
	}
	if (view == SIDE_VIEW)
	{
		s->angleX = 90.0f;
		s->angleY = 0.0f;
		s->angleZ = 0.0f;
	}
	if (view == FRONT_VIEW)
	{
		s->angleX = 0.0f;
		s->angleY = 90.0f;
		s->angleZ = -90.0f;
	}
	if (old_s)
	{
		s->scale = old_s->scale;
		s->x_off = old_s->x_off;
		s->y_off = old_s->y_off;
		s->z_off = old_s->z_off;
	}
	return (s);
}

void	ft_change_view(int state, t_vars *vars)
{
	static int	start;
	int			view;
	t_setting *view_s;
	t_setting *s;

	if (state)
		start = START_ANIMATION;
	if (!start)
		return ;

	view = ft_is_cube_clicked(vars->mouse_x, vars->mouse_y, vars);
	if (!view)
		return ;
	s = vars->setting;
	view_s = ft_get_view_setting(view, s);
	if (s->angleX != view_s->angleX)
		s->angleX += (1 - 2 * (s->angleX > view_s->angleX)) * ANGLE_STEP;
	if (s->angleY != view_s->angleY)
		s->angleY += (1 - 2 * (s->angleY > view_s->angleY)) * ANGLE_STEP;
	if (s->angleZ != view_s->angleZ)
		s->angleZ += (1 - 2 * (s->angleZ > view_s->angleZ)) * ANGLE_STEP;
	if (s->scale != view_s->scale)
		s->scale += (1 - 2 * (s->scale > view_s->scale)) * SCALE_STEP;
	if (s->x_off != view_s->x_off)
		s->x_off += (1 - 2 * (s->x_off > view_s->x_off)) * OFFSET_STEP;
	if (s->y_off != view_s->y_off)
		s->y_off += (1 - 2 * (s->y_off > view_s->y_off)) * OFFSET_STEP;
	if (s->z_off != view_s->z_off)
		s->z_off += (1 - 2 * (s->z_off > view_s->z_off)) * Z_OFFSET_STEP;
	if (s->angleX == view_s->angleX && s->angleY == view_s->angleY
			&& s->angleZ == view_s->angleZ && s->scale == view_s->scale
			&& s->x_off == view_s->x_off && s->y_off == view_s->y_off
			&& s->z_off == view_s->z_off)
		start = STOP_ANIMATION;
}

int	render_next_frame(t_vars *vars)
{
	ft_image_free(vars->mlx, vars->layout->main);
	ft_image_free(vars->mlx, vars->layout->cube_view);
	vars->layout->main = ft_init_image(vars->mlx, MAIN_W, MAIN_H);
	vars->layout->cube_view = ft_init_image(vars->mlx, CUBE_W, CUBE_H);
	ft_change_view(STOP_ANIMATION, vars);
	ft_reset_setting(0, vars->setting);
	ft_draw_main_view(vars->layout->main, vars->map, vars->setting);
	ft_draw_cube_view(vars->layout->cube_view, vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->layout->main->data, 0, 0);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->layout->cube_view->data, MAIN_W - CUBE_W, 0);
	return (0);
}

int	ft_mouse_event(int keycode, int x, int y, t_vars *vars)
{
	(void) x;
	(void) y;

	if (keycode == KEY_SCROLL_UP)
	{
		if (vars->setting->scale <= MAX_ZOOM)
			vars->setting->scale += SCALE_STEP;
	}
	if (keycode == KEY_SCROLL_DOWN)
	{
		if (vars->setting->scale > MIN_ZOOM)
			vars->setting->scale -= SCALE_STEP;
	}
	if (keycode == KEY_LEFT_CLICK)
	{
		vars->mouse_x = x;
		vars->mouse_y = y;
		ft_change_view(START_ANIMATION, vars);
	}
	return (0);
}

void	*ft_vars_free(t_vars *vars)
{
	if (vars->cube)
		free(vars->cube);
	if (vars->setting)
		free(vars->setting);
	if (vars->layout)
		ft_layout_free(vars->mlx, vars->layout);
	if (vars->map)
		ft_map_free(vars->map);
	if (vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	free(vars->mlx);// potential leaks here cuz mlx has a field for font which is an image instance;
	free(vars);
	return (NULL);
}

t_vars	*ft_vars_init(char *map_path)
{
	t_vars *vars;

	vars = (t_vars *)malloc(sizeof(t_vars));
	if (!vars)
		return (NULL);
	vars->mlx = mlx_init();	
	if (!vars->mlx)
		return (ft_vars_free(vars));
	vars->win = mlx_new_window(vars->mlx, WIN_W, WIN_H, "Fil de Fer");
	vars->map = ft_get_map_from_file(map_path);
	vars->layout = ft_layout_init(vars->mlx);
	vars->setting = init_setting();
	vars->cube = (t_point *)malloc(8 * sizeof(t_point));
	if (!vars->win || !vars->map || !vars->layout || !vars->setting || !vars->cube)
		return (ft_vars_free(vars));
	return (vars);
}

int	main(int ac, char **av)
{
	t_vars	*vars;

	if (ac != 2)
		return (1);
	vars = ft_vars_init(av[ac - 1]);
	mlx_hook(vars->win, ON_KEYDOWN, 1L<<0, ft_on_keydown, vars);
	mlx_mouse_hook(vars->win, ft_mouse_event, vars);
	mlx_hook(vars->win, ON_DESTROY, 0, ft_on_destroy, vars);
	mlx_loop_hook(vars->mlx, render_next_frame, vars);
	mlx_loop(vars->mlx);
	return (0);
}
