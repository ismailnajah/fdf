/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_text_component.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 11:12:57 by inajah            #+#    #+#             */
/*   Updated: 2024/11/24 15:35:46 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_text_draw_border(t_image *img, int x, int y)
{
	t_point a;
	t_point	b;

	a.x = x;
	a.y = y;
	a.color = C_WHITE;
	b.x = x + TEXT_FIELD_W;
	b.y = y;
	b.color = C_WHITE;
	ft_draw_line(img, a, b);
	a.x = x + TEXT_FIELD_W;
	a.y = y + TEXT_FIELD_H;
	ft_draw_line(img, b, a);
	b.x = x;
	b.y = y + TEXT_FIELD_H;
	ft_draw_line(img, a, b);
	a.x = x;
	a.y = y;
	ft_draw_line(img, a, b);
}

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

void	ft_text_field_init(t_setting *s)
{
	int i;

	s->field = (t_text_field *)malloc(SETTING_COUNT * sizeof(t_text_field));
	i = 0;
	while (i < SETTING_COUNT)
	{
		s->field[i].w = TEXT_FIELD_W;
		s->field[i].h = TEXT_FIELD_H;
		s->field[i].x = MENU_W - TEXT_FIELD_W - 10;
		s->field[i].y = MENU_H * 0.1 + (TEXT_FIELD_H + 10) * i;
		s->field[i].focused = FALSE;
		sprintf(s->field[i].text, "%.2f", ft_setting_get(s, i));
		i++;
	}
}

char	*ft_text_field(t_vars *vars, int x, int y)
{
	ft_text_draw_border(vars->layout->menu, x, y);
	return (NULL);
}
