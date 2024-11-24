/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_text_field.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 11:12:57 by inajah            #+#    #+#             */
/*   Updated: 2024/11/24 19:19:44 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_label(t_vars *vars, int x, int y, char *text)
{
	mlx_string_put(vars->mlx, vars->win, x, y, C_WHITE, text);
}

float	ft_setting_get(t_setting *s, int i)
{
	if (i == ANGLE_X)
		return (s->angleX);
	if (i == ANGLE_Y)
		return (s->angleY);
	if (i == ANGLE_Z)
		return (s->angleZ);
	if (i == SCALE)
		return (s->scale);
	if (i == X_OFF)
		return (s->x_off);
	if (i == Y_OFF)
		return (s->y_off);
	if (i == Z_OFF)
		return (s->z_off);
	return (0);
}

void	ft_setting_update_value(t_setting *s, int index)
{
	if (index == ANGLE_X)
		s->angleX = ft_atoi(s->field[index].text);
	if (index == ANGLE_Y)
		s->angleY = ft_atoi(s->field[index].text);
	if (index == ANGLE_Z)
		s->angleZ = ft_atoi(s->field[index].text);
	if (index == SCALE)
		s->scale = ft_atoi(s->field[index].text);
	if (index == X_OFF)
		s->x_off = ft_atoi(s->field[index].text);
	if (index == Y_OFF)
		s->y_off = ft_atoi(s->field[index].text);
	if (index == Z_OFF)
		s->z_off = ft_atoi(s->field[index].text);
}

int	ft_text_field_update_value(int key, t_setting *s, int cursor_start)
{
	static int cursor;
	int i;

	if (cursor_start)
	{
		cursor = 0;
		return (0);
	}
	if (key != KEY_BACK_SPACE && key != KEY_ENTER && key != '-' && (key < '0' || '9' < key))
		return (1);
	i = 0;
	while (i < SETTING_COUNT)
	{
		if (s->field[i].focused)
		{
			if (key == KEY_BACK_SPACE)
			{
				cursor = cursor - 1 * (cursor > 0);
				s->field[i].text[cursor] = '\0';
			}
			else if(key == KEY_ENTER)
			{
				s->field[i].focused = FALSE;
				global_mode(NORMAL);
				cursor = 0;
				ft_setting_update_value(s, i);
			}
			else if (cursor < TEXT_FIELD_MAX_CHAR)
			{
				s->field[i].text[cursor] = key;
				cursor++;
				s->field[i].text[cursor] = '\0';
				break;
			}
		}
		i++;
	}
	return (0);
}

void	ft_text_field_focused(t_text_field *fields, int mouse_x, int mouse_y)
{
	int i;
	int focused_index;
	t_text_field *f;

	i = 0;
	focused_index = -1;
	while (i < SETTING_COUNT)
	{
		f = fields + i;
		if (f->x <= mouse_x && mouse_x <= f->x + f->w && f->y <= mouse_y && mouse_y <= f->y + f->h)
		{
			f->focused = TRUE;
			f->text[0] = '\0';
			focused_index = i;
		}
		else
			f->focused = FALSE;
		i++;
	}
	if (focused_index >= 0)
		global_mode(INSERT);
	else
	{
		global_mode(NORMAL);
		ft_text_field_update_value(0, NULL, 1);
	}
}

void	ft_text_field_init(t_setting *s)
{
	int i;

	s->field = (t_text_field *)malloc(SETTING_COUNT * sizeof(t_text_field));
	i = 0;
	while (i < SETTING_COUNT)
	{
		s->field[i].w = TEXT_FIELD_W;
		s->field[i].h = TEXT_FIELD_H;
		s->field[i].x = MENU_W - TEXT_FIELD_W - 20;
		s->field[i].y = 10 + (TEXT_FIELD_H + 10) * i;
		s->field[i].focused = FALSE;
		sprintf(s->field[i].text, "%d", (int)ft_setting_get(s, i));
		i++;
	}
}
