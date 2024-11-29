/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 21:13:24 by inajah            #+#    #+#             */
/*   Updated: 2024/11/29 09:24:34 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_render_color_options(t_vars *vars)
{
	t_point	p;

	p.x = LP_COLOR_X;
	p.y = LP_COLOR_Y;
	p.color = C_WHITE;
	if (vars->low_p->focused)
		p.color = C_GREEN;
	ft_border_draw(vars->layout->menu, p, COLOR_W, COLOR_W);
	p.color = vars->low_p->color;
	ft_color_option_draw(vars->layout->menu, p, COLOR_W);
	p.y = HP_COLOR_Y;
	p.color = C_WHITE;
	if (vars->high_p->focused)
		p.color = C_GREEN;
	ft_border_draw(vars->layout->menu, p, COLOR_W, COLOR_W);
	p.color = vars->high_p->color;
	ft_color_option_draw(vars->layout->menu, p, COLOR_W);
}

void	render_next_frame_menu(t_vars *vars)
{
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
	ft_text_field_draw(vars);
	mlx_put_image_to_window(vars->mlx, vars->win,
		vars->layout->menu->data, 0, 0);
	ft_label_draw(vars);
}

int	render_next_frame(t_vars *vars)
{
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
	render_next_frame_menu(vars);
	return (0);
}

int	main(int ac, char **av)
{
	static t_vars	vars;

	if (ac != 2)
	{
		ft_printf("Usage: ./fdf MAP_FILE.fdf\n");
		return (1);
	}
	if (ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".fdf", 4) != 0)
		return (ft_print_error(ERR_FILE_EXTENSION));
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
