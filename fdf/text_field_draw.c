/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_field_draw.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:31:17 by inajah            #+#    #+#             */
/*   Updated: 2024/11/30 11:28:18 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	text_field_draw_border(t_image *img, t_text_field *f)
{
	t_point			a;

	a.x = f->x;
	a.y = f->y;
	a.color = C_GREEN * f->focused + C_WHITE;
	border_draw(img, a, f->w, f->h);
}

void	text_field_draw_cursor(t_vars *vars, int frames)
{
	static int	off;
	t_point		cursor_s;
	t_point		cursor_e;
	int			i;

	i = 0;
	cursor_s.color = C_WHITE;
	cursor_e.color = C_WHITE;
	cursor_s.x = vars->camera->field[i].x + 5 + vars->tf_cursor * 6;
	cursor_e.x = cursor_s.x;
	while (i < OPTION_COUNT)
	{
		if (vars->camera->field[i].focused)
		{
			cursor_s.y = vars->camera->field[i].y + 5;
			cursor_e.y = cursor_s.y + vars->camera->field[i].h - 10;
			break ;
		}
		i++;
	}
	off = !off * (frames % 200 == 0) + off * (frames % 200 != 0);
	if (i < OPTION_COUNT && !off)
		draw_line(vars->layout->menu, cursor_s, cursor_e, 1);
}

void	text_field_draw(t_vars *vars)
{
	t_text_field	*fields;
	static int		frames;
	int				i;

	fields = vars->camera->field;
	i = 0;
	while (i < OPTION_COUNT)
	{
		text_field_draw_border(vars->layout->menu, &fields[i]);
		i++;
	}
	text_field_draw_cursor(vars, frames);
	frames = (frames + 1) % 1000;
}
