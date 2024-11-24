/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 21:13:24 by inajah            #+#    #+#             */
/*   Updated: 2024/11/24 23:20:51 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <sys/time.h>
int global_mode(int m)
{
	static int mode;

	if (m == NORMAL)
		mode = m;
	if (m == INSERT)
		mode = m;
	return (mode);
}

int text_field_cursor(int m)
{
	static int cursor;

	if (m == GET_CURSOR_POS)
		return (cursor);
	cursor = m;
	return (m);
}

long long get_current_time() {
    struct timeval tv;
    gettimeofday(&tv, NULL);

    return (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000);
}

int	ft_vars_free(t_vars *vars)
{
	if (vars->cube)
		free(vars->cube);
	if (vars->camera)
		ft_camera_free(vars->camera);
	if (vars->layout)
		ft_layout_free(vars->mlx, vars->layout);
	if (vars->map)
		ft_map_free(vars->map);
	if (vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	if (vars->mlx)
		mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	return (0);
}

int	ft_vars_init(t_vars *vars, char *map_path)
{
	vars->map = ft_get_map_from_file(map_path);
	if (!vars->map)
		return (FAILURE);
	vars->mlx = mlx_init();
	if (!vars->mlx)
		return (ft_vars_free(vars), FAILURE);
	vars->win = mlx_new_window(vars->mlx, WIN_W, WIN_H, "Fil de Fer");
	vars->layout = ft_layout_init(vars->mlx);
	vars->camera = ft_camera_init();
	vars->cube = (t_point *)malloc(8 * sizeof(t_point));
	if (!vars->win || !vars->layout || !vars->camera || !vars->cube)
		return (ft_vars_free(vars));
	return (SUCCESS);
}

void	ft_text_field_border_draw(t_image *img, t_text_field *f)
{
	t_point a;
	t_point	b;
	unsigned int color;

	color = C_GREEN * f->focused + C_WHITE;
	a.x = f->x;
	a.y = f->y;
	a.color = color;
	b.x = f->x + f->w;
	b.y = f->y;
	b.color = color;
	ft_draw_line(img, a, b);
	a.x = f->x + f->w;
	a.y = f->y + f->h;
	ft_draw_line(img, b, a);
	b.x = f->x;
	b.y = f->y + f->h;
	ft_draw_line(img, a, b);
	a.x = f->x;
	a.y = f->y;
	ft_draw_line(img, a, b);
}

void	ft_render_text_fields_cursor(t_vars *vars, int frames)
{
	static int off;
	int i;
	int cursor_pos;
	t_point cursor_s;
	t_point cursor_e;

	i = 0;
	cursor_pos = text_field_cursor(GET_CURSOR_POS);
	cursor_s.color = C_WHITE;
	cursor_e.color = C_WHITE;
	cursor_s.x = vars->camera->field[i].x + 5 + cursor_pos * 6;
	cursor_e.x = cursor_s.x;
	while (i < OPTION_COUNT)
	{
		if (vars->camera->field[i].focused)
		{
			cursor_s.y = vars->camera->field[i].y + 5;
			cursor_e.y = cursor_s.y + vars->camera->field[i].h - 10;
			break;
		}
		i++;
	}
	if (frames % 300 == 0)
		off = !off;
	if (i < OPTION_COUNT && !off)
		ft_draw_line(vars->layout->menu, cursor_s, cursor_e);
}

void	ft_render_text_fields_borders(t_vars *vars)
{
	t_text_field	*fields;
	int	i;

	fields = vars->camera->field;
	i = 0;
	while (i < OPTION_COUNT)
	{
		ft_text_field_border_draw(vars->layout->menu, &fields[i]);
		i++;
	}
}

void	ft_render_labels_and_values(t_vars *vars)
{
	static char **labels_str;
	char buff[10];
	t_camera *c;
	int i;

	if (!labels_str)
		labels_str = ft_split("X-anlge [A/D],Y-angle [W/S],Z-angle [Q/E],X-offset [LEFT/RIGHT],Y-offset [UP/DOWN],Z-offset [-/+],Scale [Wheel]", ',');
	c = vars->camera;
	i = 0;
	while (i < OPTION_COUNT)
	{
		ft_label(vars, 20, c->field[i].y + c->field[i].h / 2 + 5, labels_str[i]);
		sprintf(buff, "%d", (int)c->option[i]);
		if (c->field[i].focused)
			ft_label(vars, c->field[i].x + 5, c->field[i].y + c->field[i].h / 2 + 5, c->field[i].text);
		else
			ft_label(vars, c->field[i].x + 5, c->field[i].y + c->field[i].h / 2 + 5, buff);
		i++;
	}
}

int	ft_camera_changed(t_camera *c, t_camera *old)
{
	int changed;
	int	i;

	i = 0;
	changed = 0;
	while (i < OPTION_COUNT)
	{
		if (c->option[i] != old->option[i])
		{
			old->option[i] = c->option[i];
			changed++;
		}
		i++;
	}
	return (changed > 0);
}

int	render_next_frame(t_vars *vars)
{
	static t_camera old;
	static int	frames;

	if (ft_camera_changed(vars->camera, &old))
	{
		ft_image_clear(vars->layout->main, C_BLACK);
		ft_image_clear(vars->layout->cube_view, C_BLACK);
		ft_view_change(STOP_ANIMATION, vars);
		ft_draw_main_view(vars);
		ft_draw_cube_view(vars->layout->cube_view, vars);
		mlx_put_image_to_window(vars->mlx, vars->win,
			vars->layout->main->data, MENU_W, 0);
		mlx_put_image_to_window(vars->mlx, vars->win,
			vars->layout->cube_view->data, WIN_W - CUBE_W, 0);
	}	
	//menu
	ft_image_clear(vars->layout->menu, C_GREY);
	ft_render_text_fields_borders(vars);
	ft_render_text_fields_cursor(vars, frames);
	mlx_put_image_to_window(vars->mlx, vars->win,
		vars->layout->menu->data, 0, 0);
	ft_render_labels_and_values(vars);
	frames = (frames + 1) % 100000;
	return (0);
}

int	main(int ac, char **av)
{
	static t_vars	vars;

	if (ac != 2)
		return (1);
	if (ft_vars_init(&vars, av[ac - 1]) == FAILURE)
		return (2);
	mlx_hook(vars.win, ON_KEYDOWN, 1L << 0, ft_on_keydown, &vars);
	mlx_mouse_hook(vars.win, ft_on_mouse_event, &vars);
	mlx_hook(vars.win, ON_DESTROY, 0, ft_on_destroy, &vars);
	mlx_loop_hook(vars.mlx, render_next_frame, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
