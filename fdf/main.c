/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 21:13:24 by inajah            #+#    #+#             */
/*   Updated: 2024/11/27 10:58:55 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	ft_color_picker_free(vars->color_picker);
	free(vars->labels);
	free(vars->low_p);
	free(vars->high_p);
	free(vars->mlx);
	return (0);
}

char	**ft_labels_init(void)
{
	char	**labels;

	labels = (char **)malloc(OPTION_COUNT * sizeof(char *));
	if (!labels)
		return (NULL);
	labels[0] = "X-anlge [A/D]";
	labels[1] = "Y-angle [W/S]";
	labels[2] = "Z-angle [Q/E]";
	labels[3] = "X-offset [LEFT/RIGHT]";
	labels[4] = "Y-offset [UP/DOWN]";
	labels[5] = "Z-offset [-/+]";
	labels[6] = "Scale [Wheel]";
	return (labels);
}

void	*ft_color_opt_free(t_color_opt *opt)
{
	if (!opt)
		return (NULL);
	free(opt->hue);
	free(opt->sat);
	free(opt);
	return (NULL);
}

t_color_opt *ft_color_opt_init(t_color_picker *cp)
{
	t_color_opt	*opt;

	if (!cp)
		return (NULL);
	opt = (t_color_opt *)malloc(sizeof(t_color_opt));
	if (!opt)
		return (NULL);
	opt->hue = ft_point_init(0, 0, 0, C_WHITE);
	opt->sat = ft_point_init(0, 0, 0, C_WHITE);
	opt->focused = FALSE;
	opt->color = cp->sat_cursor->color;
	if (!opt->hue || !opt->sat)
		return (ft_color_opt_free(opt));
	ft_point_copy(opt->hue, cp->hue_cursor);
	ft_point_copy(opt->sat, cp->sat_cursor);
	return (opt);
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
	vars->color_picker = ft_color_picker_init(10, MENU_H * 0.7);
	vars->cube = (t_point *)malloc(8 * sizeof(t_point));
	vars->low_p = ft_color_opt_init(vars->color_picker);
	vars->high_p = ft_color_opt_init(vars->color_picker);
	vars->labels = ft_labels_init();
	if (!vars->win || !vars->layout || !vars->camera || !vars->cube
		|| !vars->low_p || !vars->high_p || !vars->labels)
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
	static char buff[14];
	t_camera *c;
	int i;

	c = vars->camera;
	i = 0;
	while (i < OPTION_COUNT)
	{
		ft_label(vars, 20, c->field[i].y + c->field[i].h / 2 + 5, vars->labels[i]);
		sprintf(buff, "%d", (int)c->option[i]);
		if (c->field[i].focused)
			ft_label(vars, c->field[i].x + 5, c->field[i].y + c->field[i].h / 2 + 5, c->field[i].text);
		else
			ft_label(vars, c->field[i].x + 5, c->field[i].y + c->field[i].h / 2 + 5, buff);
		i++;
	}
	ft_label(vars, MENU_W * 0.2, MENU_H / 2 - 20, "Low  Point Color");
	ft_label(vars, MENU_W * 0.2, MENU_H / 2 + 40, "High Point Color");
	sprintf(buff, "0x");
	sprintf(buff + 2, "%.6X", vars->low_p->color);
	ft_label(vars, MENU_W * 0.7, MENU_H / 2 - 20, buff);
	sprintf(buff + 2, "%.6X", vars->high_p->color);
	ft_label(vars, MENU_W * 0.7, MENU_H / 2 + 40, buff);
} 

int	ft_is_camera_changed(t_camera *c, t_camera *old)
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

void	ft_render_color_opt(t_image *img, t_point p, int w)
{
	int x;
	int y;

	y = p.y + 1;
	while (y < p.y + w)
	{
		x = p.x + 1;
		while (x < p.x + w)
		{
			ft_draw_pixel(img, x, y, p.color);
			x++;
		}
		y++;
	}
}

void	ft_render_color_options(t_vars *vars)
{
	t_point p;
	
	p.x = LP_COLOR_X;
	p.y = LP_COLOR_Y;
	p.color = C_WHITE;
	if (vars->low_p->focused)
		p.color = C_GREEN;
	ft_border_draw(vars->layout->menu, p, COLOR_W, COLOR_W);
	p.color = vars->low_p->color;
	ft_render_color_opt(vars->layout->menu, p, COLOR_W);
	p.y = HP_COLOR_Y;;
	p.color = C_WHITE;
	if (vars->high_p->focused)
		p.color = C_GREEN;
	ft_border_draw(vars->layout->menu, p, COLOR_W, COLOR_W);
	p.color = vars->high_p->color;
	ft_render_color_opt(vars->layout->menu, p, COLOR_W);
}

int	ft_is_vars_changed(t_vars	*vars)
{
	static unsigned int	lp_color;
	static unsigned int	hp_color;
	static t_camera 	old;
	int					changed;

	changed = 0;
	if (vars->low_p->color != lp_color)
	{
		lp_color = vars->low_p->color;
		changed++;
	}
	if (vars->high_p->color != hp_color)
	{
		hp_color = vars->high_p->color;
		changed++;
	}
	return (changed || ft_is_camera_changed(vars->camera, &old));
}

int	render_next_frame(t_vars *vars)
{
	static int	frames;

	if (ft_is_vars_changed(vars))
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
	if (vars->low_p->focused)
	{
		ft_point_copy(vars->low_p->hue, vars->color_picker->hue_cursor);
		ft_point_copy(vars->low_p->sat, vars->color_picker->sat_cursor);
		vars->low_p->color = vars->low_p->sat->color;
	}
	else if (vars->high_p->focused)
	{
		ft_point_copy(vars->high_p->hue, vars->color_picker->hue_cursor);
		ft_point_copy(vars->high_p->sat, vars->color_picker->sat_cursor);
		vars->high_p->color = vars->high_p->sat->color;
	}
	ft_image_clear(vars->layout->menu, C_GREY);
	ft_color_picker_draw(vars->layout->menu, vars->color_picker);
	ft_render_color_options(vars);
	ft_render_text_fields_borders(vars);
	ft_render_text_fields_cursor(vars, frames);
	mlx_put_image_to_window(vars->mlx, vars->win,
		vars->layout->menu->data, 0, 0);
	ft_render_labels_and_values(vars);
	frames = (frames + 1) % 1000;
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
	mlx_hook(vars.win, ON_MOUSEUP, 1L << 3, ft_on_mouse_up, &vars);
	mlx_hook(vars.win, ON_MOUSEMOVE, 1L << 6, ft_on_mouse_move, &vars);
	mlx_mouse_hook(vars.win, ft_on_mouse_event, &vars);
	mlx_hook(vars.win, ON_DESTROY, 0, ft_on_destroy, &vars);
	mlx_loop_hook(vars.mlx, render_next_frame, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
