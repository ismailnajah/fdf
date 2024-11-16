/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:26:50 by inajah            #+#    #+#             */
/*   Updated: 2024/11/16 14:06:28 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include <stdio.h>

#define FACT 120
#define WIN_W (16 * FACT)
#define WIN_H (9 * FACT)

#define MAIN_W (WIN_W * 0.7)
#define MAIN_H WIN_H

#define TOP_W (WIN_W - MAIN_W)
#define TOP_H (WIN_H / 2)

#define SIDE_W (WIN_W - MAIN_W)
#define SIDE_H (WIN_H / 2)

#define C_WHITE 0xFFFFFFFF
#define C_RED	0x55FF0000
#define C_GREEN 0x5500FF00
#define C_BLUE  0x550000FF
#define C_BLACK 0x00000000

#define KEY_ESC 53 

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

typedef struct s_point
{
	int x;
	int y;
	int z;
}	t_point;

typedef struct s_map
{
	int width;
	int height;
	int	*values;
}	t_map;

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


typedef struct s_layout
{
	t_image	*main; // the main image where the fdf is rendered
	t_image	*top;  // top view of the fdf 
	t_image	*side; // side view of the fdf
}	t_layout;

typedef struct s_vars
{
	void		*mlx;
	void		*win;
	t_layout *layout;
}	t_vars;


int ft_fill_image(t_image *img, int w, int h, size_t color);

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
	//ft_fill_image(layout->main, MAIN_W, MAIN_H, 0x55FF0000);
	layout->top = ft_init_image(mlx, TOP_W, TOP_H);
	if (!layout->top)
		return (ft_free_layout(mlx, layout));
	ft_fill_image(layout->top, TOP_W, TOP_H, C_BLUE);
	layout->side = ft_init_image(mlx, SIDE_W, SIDE_H);
	if (!layout->side)
		return (ft_free_layout(mlx, layout));
	//ft_fill_image(layout->side, SIDE_W, SIDE_H, C_RED);
	return (layout);
}

int ft_on_keydown(int keycode, t_vars *vars)
{
	if (keycode == KEY_ESC)
	{
		ft_free_layout(vars->mlx, vars->layout);
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return (0);
}

int ft_on_destroy(t_vars *vars)
{
	ft_free_layout(vars->mlx, vars->layout);
	mlx_destroy_window(vars->mlx, vars->win);
	ft_printf("Bye\n");
	exit(0);
	return (0);
}

//draw rectangle
typedef struct s_rectangle
{
	int x;
	int y;
	int w;
	int h;
}	t_rectangle;

t_rectangle	ft_rectangle(int x, int y, int w, int h)
{
	t_rectangle rec;
	
	rec.x = x;
	rec.y = y;
	rec.w = w;
	rec.h = h;
	return (rec);
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

int ft_fill_image(t_image *img, int w, int h, size_t color)
{
	int x = 0;
	int y = 0;
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			my_mlx_pixel_put(img, x, y, ft_color_lerp(C_RED, color, (float)y / h));
			x++;
		}
		y++;
	}
	return (0);
}

void	ft_draw_rectangle(t_image *img, t_rectangle rec)
{
	int i;

	i = 0;
	while (i < rec.w)
	{
		my_mlx_pixel_put(img, rec.x + i, rec.y, C_RED);
		if (rec.h)
			my_mlx_pixel_put(img, rec.x + i, rec.y + rec.h, C_RED);
		i++;
	}
	i = 0;
	while (i < rec.h)
	{
		my_mlx_pixel_put(img, rec.x, rec.y + i, ft_color_lerp(0x000099cc, C_WHITE, (float)i / rec.h));
		if (rec.x)
			my_mlx_pixel_put(img, rec.x + rec.w, rec.y + i, ft_color_lerp(0x000099cc, C_WHITE, (float)i / rec.h));
		i++;
	}
}

void ft_swap_point(t_point *a, t_point *b)
{
	t_point tmp;

	tmp = *b;
	*b = *a;
	*a = tmp;
}
// draw a line;
void ft_draw_line(t_image *img, t_point a, t_point b)
{
	int y;
	int x;

	if (a.x == b.x)
	{
		if (a.y > b.y)
			ft_swap_point(&a, &b);
		y = a.y;
		while (y <= b.y)
		{
			my_mlx_pixel_put(img, a.x, y, C_RED);
			y++;
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
			my_mlx_pixel_put(img, x, y, C_RED);
			x++;
		}
	}
}

void ft_draw_shape(t_image *img, t_point *points, int nb)
{
	int i;

	i = 0;
	while (i < nb)
	{
		ft_draw_line(img, points[i], points[(i + 1) % nb]);
		i++;
	}
}

void ft_draw_triangle(t_image *img, int x, int y, int size)
{
	t_point points[3];
	
	points[0].x = x;
	points[0].y = y;

	points[1].x = x - size / 2;
	points[1].y = y + size;

	points[2].x = x + size / 2;
	points[2].y = y + size;

	ft_draw_shape(img, points, 3);
}

int	main(void)
{
	t_vars vars;

	vars.mlx = mlx_init();
	if (!vars.mlx)
		return (1);

	vars.win = mlx_new_window(vars.mlx, WIN_W, WIN_H, "Fil de Fer");
	vars.layout = init_layout(vars.mlx);
	if (!vars.layout)
		return (2);

	int w = 800;
	int h = 400;
	ft_draw_rectangle(vars.layout->main, ft_rectangle(MAIN_W/2 - w/2, MAIN_H/2 - h/2, w, h));

	t_point a;
	t_point b;
	a.x = 0;
	a.y = 0;
	b.x = MAIN_W;
	b.y = MAIN_H;

//	ft_draw_line(vars.layout->main, a, b);
	ft_draw_line(vars.layout->main, b, a);
	ft_draw_triangle(vars.layout->side, 200, 200, 300);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.layout->top->data, MAIN_W, 0);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.layout->side->data, MAIN_W, WIN_H / 2);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.layout->main->data, 0, 0);

	mlx_hook(vars.win, ON_KEYDOWN, 1L<<0, ft_on_keydown, &vars);
	mlx_hook(vars.win, ON_DESTROY, 0, ft_on_destroy, &vars);
	mlx_loop(vars.mlx);

	return (0);
}
