/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_event.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:18:59 by inajah            #+#    #+#             */
/*   Updated: 2025/01/26 11:58:48 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_on_destroy(t_vars *vars)
{
	ft_vars_free(vars);
	//ft_printf("[1]    1337420 segmentation fault\n");
	ft_printf(GREEN"[ INFO  ] "RESET"Window Closed\n");
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
		ft_camera_angle_update(&v->camera->option[ANGLE_X], key == KEY_D);
	if (key == KEY_S || key == KEY_W)
		ft_camera_angle_update(&v->camera->option[ANGLE_Y], key == KEY_W);
	if (key == KEY_Q || key == KEY_E)
		ft_camera_angle_update(&v->camera->option[ANGLE_Z], key == KEY_E);
	if (key == KEY_UP || key == KEY_DOWN)
		v->camera->option[Y_OFF] += (1 - 2 * (key == KEY_UP)) * Y_OFF_STEP;
	if (key == KEY_LEFT || key == KEY_RIGHT)
		v->camera->option[X_OFF] += (1 - 2 * (key == KEY_LEFT)) * X_OFF_STEP;
	if (key == KEY_PLUS || key == KEY_MINUS)
		v->camera->option[Z_OFF] += (1 - 2 * (key == KEY_MINUS)) * Z_OFF_STEP;
	if (key == KEY_SPACE)
		ft_view_change(RESET_ANIMATION, v);
	return (ft_text_field_sync_value(v->camera));
}

int lmouse_pressed = 0;

int	ft_on_mouse_event(int keycode, int x, int y, t_vars *vars)
{
	t_color_picker	*cp;

	cp = vars->color_picker;
	ft_mouse_update_position(vars, x, y);
	if (keycode == KEY_SCROLL_UP)
	{
		if (vars->camera->option[SCALE] <= MAX_ZOOM)
			ft_camera_update_zoom(vars->camera, vars->mouse, SCALE_STEP);
	}
	if (keycode == KEY_SCROLL_DOWN)
	{
		if (vars->camera->option[SCALE] > MIN_ZOOM)
			ft_camera_update_zoom(vars->camera, vars->mouse, -SCALE_STEP);
	}
	if (keycode == KEY_LEFT_CLICK)
	{
		vars->mouse->left_pressed = true;
		cp->focused = ft_color_picker_focused(cp, x, y);
		if (!vars->color_picker->focused)
			ft_color_option_focused(vars, x, y);
		ft_text_field_focused(vars, x, y);
		ft_layout_set_image_focused(vars->layout, x, y);
		ft_view_change(UPDATE_ANIMATION, vars);
	}
	return (ft_text_field_sync_value(vars->camera));
}


int	ft_on_mouse_up(int button, int x, int y, t_vars *vars)
{
	(void)x;
	(void)y;
	if (button == KEY_LEFT_CLICK)
	{
		vars->color_picker->focused = false;
		vars->mouse->left_pressed = false;
		ft_layout_reset_image_focused(vars->layout);
	}
	return (0);
}

bool is_main_focused(t_vars *vars)
{
	return (vars->layout->main->focused);
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
	else if (vars->mouse->left_pressed && is_main_focused(vars))
	{
		vars->camera->option[Y_OFF] += y - vars->mouse->y;
		vars->camera->option[X_OFF] += x - vars->mouse->x;
		ft_mouse_update_position(vars, x, y);
		return (ft_text_field_sync_value(vars->camera));
	}
	return (0);
}
