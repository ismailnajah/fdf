/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_text_field.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 11:12:57 by inajah            #+#    #+#             */
/*   Updated: 2024/11/24 23:27:31 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_label(t_vars *vars, int x, int y, char *text)
{
	mlx_string_put(vars->mlx, vars->win, x, y, C_WHITE, text);
}

int	ft_text_field_update_value(int key, t_camera *c)
{
	int	cursor;
	int i;

	cursor = text_field_cursor(GET_CURSOR_POS);
	if (key != KEY_BACK_SPACE && key != KEY_ENTER && key != '-' && (key < '0' || '9' < key))
		return (1);
	i = 0;
	while (i < OPTION_COUNT)
	{
		if (c->field[i].focused)
		{
			if (key == KEY_BACK_SPACE)
			{
				cursor = text_field_cursor(cursor - 1 * (cursor > 0));
				c->field[i].text[cursor] = '\0';
			}
			else if(key == KEY_ENTER)
			{
				c->field[i].focused = FALSE;
				global_mode(NORMAL);
				cursor = text_field_cursor(0);
				c->option[i] = atoi(c->field[i].text);
			}
			else if (cursor < TEXT_FIELD_MAX_CHAR)
			{
				c->field[i].text[cursor] = key;
				cursor = text_field_cursor(cursor + 1);
				c->field[i].text[cursor] = '\0';
				break;
			}
		}
		i++;
	}
	return (0);
}

void	ft_text_field_focused(t_camera	*c, int mouse_x, int mouse_y)
{
	int i;
	int focused_index;
	t_text_field *f;

	i = 0;
	focused_index = -1;
	while (i < OPTION_COUNT)
	{
		f = &c->field[i];
		if (f->x <= mouse_x && mouse_x <= f->x + f->w && f->y <= mouse_y && mouse_y <= f->y + f->h)
		{
			f->focused = TRUE;
			text_field_cursor(ft_strlen(f->text));
			focused_index = i;
		}
		else
		{
			f->focused = FALSE;
			sprintf(f->text, "%d", (int) c->option[i]);
		}
		i++;
	}
	if (focused_index >= 0)
		global_mode(INSERT);
	else
	{
		global_mode(NORMAL);
		text_field_cursor(0);
	}
}

t_text_field	*ft_text_field_init(t_camera *c)
{
	int					i;
	t_text_field	*field;

	field = (t_text_field *)malloc(OPTION_COUNT * sizeof(t_text_field));
	if (!field)
		return (NULL);
	i = 0;
	while (i < OPTION_COUNT)
	{
		field[i].w = TEXT_FIELD_W;
		field[i].h = TEXT_FIELD_H;
		field[i].x = MENU_W - TEXT_FIELD_W - 20;
		field[i].y = 10 + (TEXT_FIELD_H + 10) * i;
		field[i].focused = FALSE;
		sprintf(field[i].text, "%d", (int)c->option[i]);
		i++;
	}
	return (field);
}