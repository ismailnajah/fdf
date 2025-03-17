/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 21:13:24 by inajah            #+#    #+#             */
/*   Updated: 2025/03/17 13:23:44 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	render_color_options(t_vars *vars)
{
	t_point	p;

	p.x = LP_COLOR_X;
	p.y = LP_COLOR_Y;
	p.color = C_WHITE;
	if (vars->low_p->focused)
		p.color = C_GREEN;
	border_draw(vars->layout->menu, p, COLOR_W, COLOR_W);
	p.color = vars->low_p->color;
	color_option_draw(vars->layout->menu, p, COLOR_W);
	p.y = HP_COLOR_Y;
	p.color = C_WHITE;
	if (vars->high_p->focused)
		p.color = C_GREEN;
	border_draw(vars->layout->menu, p, COLOR_W, COLOR_W);
	p.color = vars->high_p->color;
	color_option_draw(vars->layout->menu, p, COLOR_W);
}

void	render_next_frame_menu(t_vars *vars)
{
	if (vars->low_p->focused)
	{
		point_copy(vars->low_p->hue, vars->color_picker->hue_cursor);
		point_copy(vars->low_p->sat, vars->color_picker->sat_cursor);
		vars->low_p->color = vars->low_p->sat->color;
	}
	else if (vars->high_p->focused)
	{
		point_copy(vars->high_p->hue, vars->color_picker->hue_cursor);
		point_copy(vars->high_p->sat, vars->color_picker->sat_cursor);
		vars->high_p->color = vars->high_p->sat->color;
	}
	image_clear(vars->layout->menu, C_GREY);
	color_picker_draw(vars->layout->menu, vars->color_picker);
	render_color_options(vars);
	text_field_draw(vars);
	mlx_put_image_to_window(vars->mlx, vars->win,
		vars->layout->menu->data, 0, 0);
	label_draw(vars);
}

int	render_next_frame(t_vars *vars)
{
	if (is_vars_changed(vars))
	{
		image_clear(vars->layout->main, C_BLACK);
		image_clear(vars->layout->cube_view, C_BLACK);
		view_change(STOP_ANIMATION, vars);
		draw_main_view(vars);
		draw_cube_view(vars->layout->cube_view, vars);
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
		printf("Usage: ./fdf filename.fdf\n");
		return (1);
	}
	if (!is_valid_file(av[1]))
		return (2);
	if (vars_init(&vars, av[ac - 1]) == FAILURE)
		return (3);
	mlx_hook(vars.win, ON_KEYDOWN, 1L << 0, on_keydown, &vars);
	mlx_hook(vars.win, ON_MOUSEUP, 1L << 3, on_mouse_up, &vars);
	mlx_hook(vars.win, ON_MOUSEMOVE, 1L << 6, on_mouse_move, &vars);
	mlx_mouse_hook(vars.win, on_mouse_event, &vars);
	mlx_hook(vars.win, ON_DESTROY, 0, on_destroy, &vars);
	mlx_loop_hook(vars.mlx, render_next_frame, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
