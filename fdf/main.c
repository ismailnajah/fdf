/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:26:50 by inajah            #+#    #+#             */
/*   Updated: 2024/11/19 14:06:44 by inajah           ###   ########.fr       */
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

void	*ft_free_image(void *mlx, t_image *img)
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
		return (ft_free_image(mlx, img));
	img->w = width;
	img->h = height;
	return (img);
}

void* ft_free_layout(void *mlx, t_layout *layout)
{
	if (!layout)
		return (NULL);
	ft_free_image(mlx, layout->main);
	ft_free_image(mlx, layout->top);
	ft_free_image(mlx, layout->side);
	free(layout);
	return (NULL);
}

t_layout *init_layout(void* mlx)
{
	t_layout *layout;

	layout = (t_layout*)ft_calloc(1, sizeof(t_layout));
	if(!layout)
		return (NULL);
	layout->main = ft_init_image(mlx, MAIN_W, MAIN_H);
	if (!layout->main)
		return (ft_free_layout(mlx, layout));
	layout->top = ft_init_image(mlx, TOP_W, TOP_H);
	if (!layout->top)
		return (ft_free_layout(mlx, layout));
	layout->side = ft_init_image(mlx, SIDE_W, SIDE_H);
	if (!layout->side)
		return (ft_free_layout(mlx, layout));
	return (layout);
}

float	ft_clamp(float value, float min, float max)
{
	if (value <= min || value >= max)
		return (0.0f);
	return (value);
}

int ft_on_keydown(int keycode, t_vars *vars)
{
	if (keycode == KEY_ESC)
	{
		ft_free_layout(vars->mlx, vars->layout);
		free(vars->setting);
		ft_free_map(vars->map);
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	if (keycode == KEY_W)
		vars->setting->angleX = ft_clamp(vars->setting->angleX + ANGLE_STEP, -360.0f, 360.0f);
	if (keycode == KEY_S)
		vars->setting->angleX = ft_clamp(vars->setting->angleX - ANGLE_STEP, -360.0f, 360.0f);
	if (keycode == KEY_D)
		vars->setting->angleY = ft_clamp(vars->setting->angleY + ANGLE_STEP, -360.0f, 360.0f);
	if (keycode == KEY_A)
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
	//printf("keycode: %d\n", keycode);
	return (0);
}

int ft_on_destroy(t_vars *vars)
{
	ft_free_layout(vars->mlx, vars->layout);
	free(vars->setting);
	ft_free_map(vars->map);
	mlx_destroy_window(vars->mlx, vars->win);
	ft_printf("Bye\n");
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

void ft_swap_point(t_point *a, t_point *b)
{
	t_point tmp;

	tmp = *b;
	*b = *a;
	*a = tmp;
}
// draw a line;
void ft_draw_line_lerp(t_image *img, t_point a, t_point b)
{
	float y;
	float x;

	if (a.x == b.x)
	{
		if (a.y > b.y)
			ft_swap_point(&a, &b);
		y = a.y;
		while (y <= b.y)
		{
			my_mlx_pixel_put(img, a.x, y, ft_color_lerp(a.color, b.color, (float)y / b.y));
			y += 0.1;
		}
	} 
	else
	{
		if (a.x > b.x)
			ft_swap_point(&a, &b);
		x = a.x;
		while (x <= b.x)
		{
			y = (a.y * (b.x - x) + b.y * (x - a.x)) / (b.x - a.x);
			my_mlx_pixel_put(img, x, y, ft_color_lerp(a.color, b.color, (float)x / b.x));
			x += 0.1;
		}
	}
}
// TODO: fix the order of render (always go back to front);
void	ft_draw_line_dda(t_image *img, t_point a, t_point b)
{
	float	dx;
	float	dy;
	float	x;
	float	y;
	float	steps;
	int		i;

	dx = b.x - a.x;
	dy = b.y - a.y;
	if(fabs(dx) > fabs(dy))
		steps = dx;
	else
		steps = dy;
	i = 0;
	x = a.x;//(a.x > b.x) * b.x + (a.x <= b.x) * a.x;
	y = a.y;//(a.x > b.x) * b.y + (a.x <= b.x) * a.y;
	printf("[ INFO ] drawing a line from (%.2f, %.2f) to (%.2f, %.2f)\n", a.x, a.y, b.x, b.y);
	printf("[ INFO ] x=%.2f y=%.2f steps=%.2f dx=%.2f dy=%.2f\n", x, y, steps, dx, dy);
	while (i < steps)
	{
		printf("");
		my_mlx_pixel_put(img, lround(x), lround(y), ft_color_lerp(a.color, b.color, x / steps));
		x = x + dx / steps;
		y = y + dy / steps;
		i++;
	}
} 

void	ft_draw_line(t_image *img, t_point a, t_point b)
{
	//linear interpolation
	ft_draw_line_lerp(img, a, b);
	//DDA
	//ft_draw_line_dda(img, a, b);
}

void	ft_draw_projection(t_image *img, t_map *map, t_setting *s)
{
	int	i;
	int j;
	t_point a;
	t_point b;

	j = 0;
	while (j < map->h)
	{
		i = 0;
		while (i < map->w)
		{
			a.x = map->points[j * map->w + i].x * s->scale + s->x_off;
			a.y = map->points[j * map->w + i].y * s->scale + s->y_off;
			a.color = map->points[j * map->w + i].color;

			if (i + 1 < map->w)
			{
				b.x = map->points[j * map->w + i + 1].x * s->scale + s->x_off;
				b.y = map->points[j * map->w + i + 1].y * s->scale + s->y_off;
				b.color = map->points[j * map->w + i + 1].color;
				ft_draw_line(img, a, b);
			}
			if (j + 1 < map->h)
			{
				b.x = map->points[(j + 1) * map->w + i].x * s->scale + s->x_off;
				b.y = map->points[(j + 1) * map->w + i].y * s->scale + s->y_off;
				b.color = map->points[(j + 1) * map->w + i].color;
				ft_draw_line(img, a, b);
			}
			i++;
		}
		j++;
	}
}

void	ft_draw_main_view(t_image *img, t_map *map, t_setting *s)
{
	t_map		*new_map;
	t_point		px;
	t_point		py;
	t_matrix	*rotateX;
	t_matrix	*rotateY;
	t_matrix	*rotateZ;

	int		i;
	int		j;

	new_map = ft_init_map(map->w, map->h);
	if (!new_map)
		return ;
	rotateX = ft_matrix_init(3, 3);
	if (!rotateX)
		return ;
	rotateY = ft_matrix_init(3, 3);
	if (!rotateY)
		return ;
	rotateZ = ft_matrix_init(3, 3);
	if (!rotateZ)
		return ;

	ft_matrix_rotateX(rotateX, s->angleX);
	ft_matrix_rotateY(rotateY, s->angleY);
	ft_matrix_rotateZ(rotateZ, s->angleZ);
	j = 0;
	while (j < new_map->h)
	{
		i = 0;
		while (i < new_map->w)
		{
			ft_matrix_point_mul(rotateX, &map->points[j * map->w + i], &px);
			ft_matrix_point_mul(rotateY, &px, &py);
			ft_matrix_point_mul(rotateZ, &py, &new_map->points[j * new_map->w + i]);
			i++;
		}
		j++;
	}
	ft_draw_projection(img, new_map, s);
	ft_matrix_free(rotateX);
	ft_matrix_free(rotateY);
	ft_matrix_free(rotateZ);
	ft_free_map(new_map);
}

int	render_next_frame(t_vars *vars)
{
	ft_free_image(vars->mlx, vars->layout->main);	
	vars->layout->main = ft_init_image(vars->mlx, MAIN_W, MAIN_H);
	ft_draw_main_view(vars->layout->main, vars->map, vars->setting);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->layout->main->data, 0, 0);
	return (0);
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
	return (s);
}

int	ft_mouse_event(int keycode, int x, int y, t_vars *vars)
{
	(void) x;
	(void) y;
	int	scale;

	scale = (MAX_ZOOM - MIN_ZOOM) / SCALE_STEP;
	if (keycode == KEY_SCROLL_UP)
	{
		if (vars->setting->scale <= MAX_ZOOM)
			vars->setting->scale += scale;
	}
	if (keycode == KEY_SCROLL_DOWN)
	{
		if (vars->setting->scale > MIN_ZOOM)
			vars->setting->scale -= scale;
	}
	//printf("[ INFO ] (%d, %d) Mouse button (%d) clicked! (scale = %d)\n", x, y, keycode, scale);
	return (0);
}

int	main(int ac, char **av)
{
	t_vars	vars;

	if (ac != 2)
		return (1);
	vars.map = ft_get_map_from_file(av[1]);
	if (!vars.map)
		return (1);
	//ft_debug_map(map);
	vars.mlx = mlx_init();
	if (!vars.mlx)
		return (2);
	vars.win = mlx_new_window(vars.mlx, WIN_W, WIN_H, "Fil de Fer");
	if (!vars.win)
		return (3);
	vars.layout = init_layout(vars.mlx);
	if (!vars.layout)
		return (4);
	vars.setting = init_setting();
	if (!vars.setting)
		return (5);
	mlx_hook(vars.win, ON_KEYDOWN, 1L<<0, ft_on_keydown, &vars);
	mlx_mouse_hook(vars.win, ft_mouse_event, &vars);
	mlx_hook(vars.win, ON_DESTROY, 0, ft_on_destroy, &vars);
	mlx_loop_hook(vars.mlx, render_next_frame, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
