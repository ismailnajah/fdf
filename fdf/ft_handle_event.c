/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_event.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:18:59 by inajah            #+#    #+#             */
/*   Updated: 2024/11/28 17:25:10 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_on_destroy(t_vars *vars)
{
	ft_vars_free(vars);
	ft_printf("[ INFO  ] Window Closed\n");
	exit(0);
	return (0);
}

int	ft_on_keydown(int key, t_vars *v)
{
	if (key == KEY_ESC)
		ft_on_destroy(v);
	if (v->global_mode == INSERT)
		return (ft_text_field_event(key, v));
	if (key == KEY_A || key == KEY_D)
		ft_angle_change(&v->camera->option[ANGLE_X], key == KEY_D);
	if (key == KEY_S || key == KEY_W)
		ft_angle_change(&v->camera->option[ANGLE_Y], key == KEY_W);
	if (key == KEY_Q || key == KEY_E)
		ft_angle_change(&v->camera->option[ANGLE_Z], key == KEY_E);
	if (key == KEY_UP || key == KEY_DOWN)
		v->camera->option[Y_OFF] += (1 - 2 * (key == KEY_UP)) * OFFSET_STEP;
	if (key == KEY_LEFT || key == KEY_RIGHT)
		v->camera->option[X_OFF] += (1 - 2 * (key == KEY_LEFT)) * OFFSET_STEP;
	if (key == KEY_PLUS || key == KEY_MINUS)
	{
		ft_scale_z(v->map, 1 + (1 - 2 * (key == KEY_PLUS)) * Z_STEP);
		v->camera->option[Z_OFF] -= (1 - 2 * (key == KEY_PLUS));
	}
	if (key == KEY_SPACE)
		ft_view_change(RESET_ANIMATION, v);
	return (ft_text_field_sync_value(v->camera));
}

int	ft_on_mouse_event(int keycode, int x, int y, t_vars *vars)
{
	t_color_picker	*cp;

	cp = vars->color_picker;
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
		cp->focused = ft_color_picker_focused(cp, x, y);
		if (!vars->color_picker->focused)
			ft_color_option_focused(vars, x, y);
		ft_text_field_focused(vars, x, y);
		ft_view_change(UPDATE_ANIMATION, vars);
	}
	return (ft_text_field_sync_value(vars->camera));
}

int	ft_on_mouse_up(int button, int x, int y, t_vars *vars)
{
	(void)x;
	(void)y;
	if (button == KEY_LEFT_CLICK)
		vars->color_picker->focused = FALSE;
	return (0);
}

int	ft_on_mouse_move(int x, int y, t_vars *vars)
{
	if (vars->color_picker->focused)
	{
		if (y <= vars->color_picker->y)
			y = vars->color_picker->y + 1;
		if (y >= vars->color_picker->y + vars->color_picker->hue->h)
			y = vars->color_picker->y + vars->color_picker->hue->h - 1;
		if (vars->color_picker->focused == CP_HUE)
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
