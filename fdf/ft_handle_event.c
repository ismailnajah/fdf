/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_event.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:18:59 by inajah            #+#    #+#             */
/*   Updated: 2024/11/24 22:39:48 by inajah           ###   ########.fr       */
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
	return (0);
}

int	ft_on_destroy(t_vars *vars)
{
	ft_vars_free(vars);
	ft_printf("[ INFO  ] Window Closed\n");
	exit(0);
	return (0);
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
		ft_text_field_focused(vars->camera->field, x, y);
		ft_view_change(UPDATE_ANIMATION, vars);
	}
	return (0);
}
