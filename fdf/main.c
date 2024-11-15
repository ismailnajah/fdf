/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:26:50 by inajah            #+#    #+#             */
/*   Updated: 2024/11/15 20:52:48 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include <stdio.h>

#define FACT 50
#define WIN_WIDTH (16 * FACT)
#define WIN_HEIGHT (9 * FACT)

#define MAIN_WIDTH (WIN_WIDTH * 0.7)
#define MAIN_HEIGHT WIN_HEIGHT

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
}	t_image;


typedef struct s_layout
{
	t_image	main; // the main image where the fdf is rendered
	t_image	top;  // top view of the fdf 
	t_image	side; // side view of the fdf
}	t_layout;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
}	t_vars;

int close_window(int keycode, t_vars *vars)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return (0);
}

int close_program(t_vars *vars)
{
	(void) vars;
	printf("Bye\n");
	exit(0);
	return (0);
}

void my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*) dst = color;
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
			my_mlx_pixel_put(img, x, y, color);
			x++;
		}
		y++;
	}
	return (0);
}

t_layout init_layout(void* mlx)
{
	t_image main;
	t_image top;
	t_image side;

	main.data = mlx_new_image(mlx, MAIN_WIDTH, MAIN_HEIGHT);
	main.addr = mlx_get_data_addr(main.data, &main.bits_per_pixel, &main.line_length, &main.endian);
	ft_fill_image(&main, MAIN_WIDTH, MAIN_HEIGHT, 0x00FF0000);

	top.data = mlx_new_image(mlx, WIN_WIDTH - MAIN_WIDTH, WIN_HEIGHT/2);
	top.addr = mlx_get_data_addr(top.data, &top.bits_per_pixel, &top.line_length, &top.endian);
	ft_fill_image(&top, WIN_WIDTH - MAIN_WIDTH, WIN_HEIGHT/2, 0x0000FF00);

	side.data = mlx_new_image(mlx, WIN_WIDTH - MAIN_WIDTH, WIN_HEIGHT/2);
	side.addr = mlx_get_data_addr(side.data, &side.bits_per_pixel, &side.line_length, &side.endian);
	ft_fill_image(&side, WIN_WIDTH - MAIN_WIDTH, WIN_HEIGHT/2, 0x000000FF);

	t_layout layout;
	layout.main = main;
	layout.top = top;
	layout.side = side;
	return (layout);
}

int	main(void)
{
	t_vars vars;
	t_layout layout;

	vars.mlx = mlx_init();
	if (!vars.mlx)
		return (1);

	vars.win = mlx_new_window(vars.mlx, WIN_WIDTH, WIN_HEIGHT, "Fil de Fer");
	layout = init_layout(vars.mlx);

	mlx_put_image_to_window(vars.mlx, vars.win, layout.top.data, MAIN_WIDTH, 0);
	mlx_put_image_to_window(vars.mlx, vars.win, layout.side.data, MAIN_WIDTH, WIN_HEIGHT/2);
	mlx_put_image_to_window(vars.mlx, vars.win, layout.main.data, 0, 0);

	mlx_hook(vars.win, ON_KEYDOWN, 1L<<0, close_window, &vars);
	mlx_hook(vars.win, ON_DESTROY, 0, close_program, &vars);
	mlx_loop(vars.mlx);

	return (0);
}
