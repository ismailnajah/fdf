/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_text_field.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 11:12:57 by inajah            #+#    #+#             */
/*   Updated: 2024/11/27 14:08:59 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_text_field_sync_value(t_camera *c)
{
	int	i;

	i = 0;
	while (i < OPTION_COUNT)
	{
		sprintf(c->field[i].text, "%d", (int)c->option[i]);
		i++;
	}
	return (0);
}

void	ft_text_field_update_value(int key, t_vars *vars, int i)
{
	t_camera	*c;

	c = vars->camera;
	if (key == KEY_BACK_SPACE)
	{
		vars->tf_cursor -= 1 * (vars->tf_cursor > 0);
		c->field[i].text[vars->tf_cursor] = '\0';
	}
	else if (key == KEY_ENTER)
	{
		c->field[i].focused = FALSE;
		vars->global_mode = NORMAL;
		vars->tf_cursor = 0;
		c->option[i] = atoi(c->field[i].text);
		sprintf(c->field[i].text, "%d", (int)c->option[i]);
	}
	else if (vars->tf_cursor < TEXT_FIELD_MAX_CHAR)
	{
		c->field[i].text[vars->tf_cursor] = key;
		vars->tf_cursor++;
		c->field[i].text[vars->tf_cursor] = '\0';
	}
}

int	ft_text_field_event(int key, t_vars *vars)
{
	int			i;
	t_camera	*c;

	c = vars->camera;
	if (key != KEY_BACK_SPACE && key != KEY_ENTER
		&& key != '-' && (key < '0' || '9' < key))
		return (1);
	i = 0;
	while (i < OPTION_COUNT)
	{
		if (c->field[i].focused)
		{
			ft_text_field_update_value(key, vars, i);
			break ;
		}
		i++;
	}
	return (0);
}

void	ft_text_field_focused(t_vars *vars, int mouse_x, int mouse_y)
{
	int				i;
	int				focused;
	t_text_field	*f;

	i = 0;
	focused = FALSE;
	while (i < OPTION_COUNT)
	{
		f = &vars->camera->field[i];
		f->focused = FALSE;
		if (f->x <= mouse_x && mouse_x <= f->x + f->w
			&& f->y <= mouse_y && mouse_y <= f->y + f->h)
		{
			f->focused = TRUE;
			focused = TRUE;
			vars->tf_cursor = ft_strlen(f->text);
		}
		i++;
	}
	vars->global_mode = INSERT * focused + NORMAL * !focused;
}

t_text_field	*ft_text_field_init(t_camera *c)
{
	int				i;
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
		field[i].y = 50 + (TEXT_FIELD_H + 10) * i;
		field[i].focused = FALSE;
		sprintf(field[i].text, "%d", (int)c->option[i]);
		i++;
	}
	return (field);
}
