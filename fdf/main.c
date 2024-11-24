/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 21:13:24 by inajah            #+#    #+#             */
/*   Updated: 2024/11/24 15:49:41 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_vars_free(t_vars *vars)
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
	vars->setting = ft_setting_init();
	vars->cube = (t_point *)malloc(8 * sizeof(t_point));
	if (!vars->win || !vars->layout || !vars->setting || !vars->cube)
		return (ft_vars_free(vars));
	return (SUCCESS);
}

void	ft_text_field_border_draw(t_image *img, t_text_field *f)
{
	t_point a;
	t_point	b;
	unsigned int color;

	if (f->focused)
		color = C_GREEN;
	else
		color = C_WHITE;
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

void	ft_render_text_fields_borders(t_vars *vars)
{
	t_text_field	*fields;
	int	i;

	fields = vars->setting->field;
	i = 0;
	while (i < SETTING_COUNT)
	{
		ft_text_field_border_draw(vars->layout->menu, &fields[i]);
		i++;
	}
}

void	ft_render_labels_and_values(t_vars *vars)
{
	static char **labels_str;
	char buff[10];
	t_setting *s;
	int i;

	if (!labels_str)
	{
		labels_str = ft_split("X-axis anlge,Y-axis angle,Z-axis angle,Scale,X-offset,Y-offset,Z-offset", ',');
	}
	s = vars->setting;
	i = 0;
	while (i < SETTING_COUNT)
	{
		ft_label(vars, 20, s->field[i].y + s->field[i].h / 2 + 5, labels_str[i]);
		sprintf(buff, "%.2f", ft_setting_get(s, i));
		ft_label(vars, MENU_W - s->field[i].w + 20, s->field[i].y + s->field[i].h / 2 + 5, buff);
		i++;
	}
}

int	render_next_frame(t_vars *vars)
{
	ft_image_clear(vars->layout->main, C_BLACK);
	ft_image_clear(vars->layout->cube_view, C_BLACK);
	ft_view_change(STOP_ANIMATION, vars);
	ft_draw_main_view(vars);
	ft_draw_cube_view(vars->layout->cube_view, vars);
	
	ft_render_text_fields_borders(vars);
	mlx_put_image_to_window(vars->mlx, vars->win,
		vars->layout->main->data, MENU_W, 0);
	mlx_put_image_to_window(vars->mlx, vars->win,
		vars->layout->cube_view->data, WIN_W - CUBE_W, 0);
	mlx_put_image_to_window(vars->mlx, vars->win,
		vars->layout->menu->data, 0, 0);

	ft_render_labels_and_values(vars);
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
