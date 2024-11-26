/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_event.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:18:59 by inajah            #+#    #+#             */
/*   Updated: 2024/11/26 19:26:34 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_on_keydown(int keycode, t_vars *vars)
{
	if (keycode == KEY_ESC)
	{
		ft_vars_free(vars);
		exit(0);
	}
	if (global_mode(GET_MODE) == INSERT)
		return (ft_text_field_update_value(keycode, vars->camera));
	if (keycode == KEY_A || keycode == KEY_D)
		ft_angle_change(&vars->camera->option[ANGLE_X], keycode == KEY_D);
	if (keycode == KEY_S || keycode == KEY_W)
		ft_angle_change(&vars->camera->option[ANGLE_Y], keycode == KEY_W);
	if (keycode == KEY_Q || keycode == KEY_E)
		ft_angle_change(&vars->camera->option[ANGLE_Z], keycode == KEY_E);
	if (keycode == KEY_UP || keycode == KEY_DOWN)
		vars->camera->option[Y_OFF] += (1 - 2 * (keycode == KEY_UP)) * OFFSET_STEP;
	if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
		vars->camera->option[X_OFF] += (1 - 2 * (keycode == KEY_LEFT)) * OFFSET_STEP;
	if (keycode == KEY_PLUS || keycode == KEY_MINUS)
	{
		ft_scale_z(vars->map, 1 + (1 - 2 * (keycode == KEY_PLUS)) * Z_STEP);
		vars->camera->option[Z_OFF] -= (1 - 2 * (keycode == KEY_PLUS));
	}
	if (keycode == KEY_SPACE)
		ft_view_change(RESET_ANIMATION, vars);
	return (ft_text_field_sync_value(vars->camera));
}

int	ft_on_destroy(t_vars *vars)
{
	ft_vars_free(vars);
	ft_printf("[ INFO  ] Window Closed\n");
	exit(0);
	return (0);
}

void	ft_color_option_focused(int x, int y)
{
	if (LP_COLOR_X < x && x < LP_COLOR_X + COLOR_W)
	{
		if (LP_COLOR_Y < y && y < LP_COLOR_Y + COLOR_W)
			color_option_focused(1);
		else if (HP_COLOR_Y < y && y < HP_COLOR_Y + COLOR_W)
			color_option_focused(2);
	}
}

int	ft_on_mouse_event(int keycode, int x, int y, t_vars *vars)
{
	if (keycode == KEY_SCROLL_UP)
	{
		if (vars->camera->option[SCALE] <= MAX_ZOOM)
			vars->camera->option[SCALE] += SCALE_STEP;
	}
	if (keycode == KEY_SCROLL_DOWN)
	{
		if (vars->camera->option[SCALE] > MIN_ZOOM)
			vars->camera->option[SCALE] -= SCALE_STEP;
	}
	if (keycode == KEY_LEFT_CLICK)
	{
		vars->mouse_x = x;
		vars->mouse_y = y;
		vars->mouse_up = ft_color_picker_focused(vars->color_picker, x, y);
		ft_color_option_focused(x, y);
		ft_text_field_focused(vars->camera, x, y);
		ft_view_change(UPDATE_ANIMATION, vars);
	}
	return (ft_text_field_sync_value(vars->camera));
}

int	ft_on_mouse_up(int button, int x, int y, t_vars *vars)
{
	(void)x;
	(void)y;
	if (button == KEY_LEFT_CLICK)
		vars->mouse_up = 0;
	return (0);
}

int	ft_on_mouse_move(int x, int y, t_vars *vars)
{
	if (vars->color_picker->visible && vars->mouse_up)
	{
		if (y <= vars->color_picker->y)
			y = vars->color_picker->y + 1;
		if (y >= vars->color_picker->y + vars->color_picker->hue->h)
			y = vars->color_picker->y + vars->color_picker->hue->h - 1;
		if (vars->mouse_up == 1)
			x = vars->color_picker->hue->x + vars->color_picker->hue->w / 2;
		else
		{
			if (x <= vars->color_picker->x)
				x = vars->color_picker->x + 1;
			else if (x >= vars->color_picker->x + vars->color_picker->sat->w)
				x = vars->color_picker->x + vars->color_picker->sat->w - 1; 
		}
		ft_color_picker_focused(vars->color_picker, x, y);
	}
	return (0);
}
