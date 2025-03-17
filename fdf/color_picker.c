/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_picker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 08:40:17 by inajah            #+#    #+#             */
/*   Updated: 2024/11/28 15:28:54 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	color_picker_draw_hue(t_image *img, t_color_picker *cp)
{
	t_point			a;
	unsigned int	color;

	rect_draw(img, cp->hue, C_WHITE);
	color = C_RED;
	a.y = cp->hue->y + 1;
	while (a.y < cp->hue->y + cp->hue->h)
	{
		a.x = cp->hue->x + 1;
		while (a.x < cp->hue->x + cp->hue->w)
			draw_pixel(img, a.x++, a.y, color);
		if (a.y == cp->hue_cursor->y)
			cp->hue_cursor->color = color;
		color = next_color(color);
		a.y++;
	}
	point_copy(&a, cp->hue_cursor);
	a.color = C_BLACK;
	border_draw(img, a, cp->hue->w, 2);
}

void	color_picker_draw_sat(t_image *img, t_color_picker *cp)
{
	unsigned int	c1;
	unsigned int	c2;
	float			step;
	t_point			p;

	rect_draw(img, cp->sat, C_WHITE);
	p.y = cp->y + 1;
	while (p.y < cp->sat->y + cp->sat->h)
	{
		step = (p.y - cp->sat->y) / cp->sat->h;
		c1 = color_lerp(C_WHITE, C_BLACK, step);
		c2 = color_lerp(cp->hue_cursor->color, C_BLACK, step);
		p.x = cp->sat->x + 1;
		while (p.x < cp->sat->x + cp->sat->w)
		{
			step = (p.x - cp->sat->x) / cp->sat->w;
			p.color = color_lerp(c1, c2, step);
			draw_pixel(img, p.x, p.y, p.color);
			p.x++;
			if (p.x == cp->sat_cursor->x && p.y == cp->sat_cursor->y)
				cp->sat_cursor->color = p.color;
		}
		p.y++;
	}
	circle_draw(img, *cp->sat_cursor);
}

void	color_picker_draw(t_image *img, t_color_picker *cp)
{
	color_picker_draw_hue(img, cp);
	color_picker_draw_sat(img, cp);
}

void	*color_picker_free(t_color_picker *cp)
{
	if (!cp)
		return (NULL);
	free(cp->sat);
	free(cp->sat_cursor);
	free(cp->hue);
	free(cp->hue_cursor);
	free(cp);
	return (NULL);
}

t_color_picker	*color_picker_init(int x, int y)
{
	t_color_picker	*cp;

	cp = (t_color_picker *)malloc(sizeof(t_color_picker));
	if (!cp)
		return (NULL);
	cp->x = x;
	cp->y = y;
	cp->focused = FALSE;
	cp->sat = rect_init(cp->x, cp->y, 300, 300);
	cp->sat_cursor = point_init(cp->sat->x + 1, cp->sat->y + 1, 0, C_WHITE);
	cp->hue = rect_init(cp->sat->x + cp->sat->w + 20,
			cp->sat->y, MENU_W * 0.1, cp->sat->h);
	cp->hue_cursor = point_init(cp->hue->x, cp->hue->y + 1 / 2, 0, C_WHITE);
	if (!cp->sat || !cp->sat_cursor || !cp->hue || !cp->hue_cursor)
		return (NULL);
	return (cp);
}
