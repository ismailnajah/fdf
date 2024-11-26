/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color_picker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 08:40:17 by inajah            #+#    #+#             */
/*   Updated: 2024/11/26 17:31:52 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point *ft_point_init(float x, float y, float z, unsigned int color)
{
	t_point	*p;

	p = (t_point *)malloc(sizeof(t_point));
	p->x = x;
	p->y = y;
	p->z = z;
	p->color = color;
	return (p);
}

t_rectangle *ft_rectangle_init(int x, int y, int w, int h)
{
	t_rectangle	*rec;

	rec = (t_rectangle *)malloc(sizeof(t_rectangle));
	rec->x = x;
	rec->y = y;
	rec->w = w;
	rec->h = h;
	return (rec);
}

void	ft_border_draw(t_image *img, t_point a, int w, int h)
{
	t_point	b;

	b.x = a.x + w;
	b.y = a.y;
	b.color = a.color;
	ft_draw_line(img, a, b);
	b.x = a.x;
	b.y = a.y + h;
	ft_draw_line(img, b, a);
	a.x = a.x + w;
	a.y = a.y + h;
	ft_draw_line(img, a, b);
	b.x = a.x;
	b.y = a.y - h;
	ft_draw_line(img, a, b);
}

void	ft_color_picker_hue_draw(t_image *img, t_color_picker *cp)
{
	t_point	a;
	int step = 5;
	int	r;
	int g;
	int b;

	a.x = cp->hue->x;
	a.y = cp->hue->y;
	a.color = C_WHITE;
	ft_border_draw(img, a, cp->hue->w, cp->hue->h);
	r = 255;
	g = 0;
	b = 0;
	a.y = cp->hue->y + 1;
	while (a.y < cp->hue->y + cp->hue->h)
	{
		a.x = cp->hue->x + 1;
		while (a.x < cp->hue->x + cp->hue->w)
		{
			a.color = create_trgb(0, r, g, b);
			ft_draw_pixel(img, a.x, a.y, a.color);
			a.x++;
		}
		r += step * (r != 255 && g == 0 && b == 255) - step * (r != 0 && g == 255 && b == 0);
		g += step * (r == 255 && g != 255 && b == 0) - step * (r == 0 && g != 0 && b == 255);
		b += step * (r == 0 && g == 255 && b != 255) - step * (r == 255 && g == 0 && b != 0);
		if (a.y == cp->hue_cursor->y)
			cp->hue_cursor->color = a.color;
		a.y++;
	}
	t_point	d;
	d = *cp->hue_cursor;
	d.color = C_BLACK;
	ft_border_draw(img, d, cp->hue->w, 2);
}

unsigned int ft_color_picker_hue(t_image *img, t_color_picker *cp)
{
	int x;
	int y;

	x = cp->hue_cursor->x + cp->hue->w / 2;
	y = cp->hue_cursor->y;
	int pos = (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (img->addr[pos]);
}

void ft_draw_circle(t_image *img, int center_x, int center_y, unsigned int color)
{
    int radius = 10;
	int x = radius;
    int y = 0;
    int radius_error = 1 - radius;
    
    while (x >= y) {
        ft_draw_pixel(img, center_x + x, center_y + y, color);
        ft_draw_pixel(img, center_x + y, center_y + x, color);
        ft_draw_pixel(img, center_x - y, center_y + x, color);
        ft_draw_pixel(img, center_x - x, center_y + y, color);
        ft_draw_pixel(img, center_x - x, center_y - y, color);
        ft_draw_pixel(img, center_x - y, center_y - x, color);
        ft_draw_pixel(img, center_x + y, center_y - x, color);
        ft_draw_pixel(img, center_x + x, center_y - y, color); 
        y++;
        if (radius_error < 0) {
            radius_error += 2 * y + 1;
        } else {
            x--;
            radius_error += 2 * (y - x + 1);
        }
    }
}

void	ft_color_picker_sat_draw(t_image *img, t_color_picker *cp)
{
	unsigned int	c1;
	unsigned int	c2;
	int				x;
	int				y;
	float			step;
	t_point			a;

	a.x = cp->sat->x;
	a.y = cp->sat->y;
	a.color = C_WHITE;
	ft_border_draw(img, a, cp->sat->w, cp->sat->h);
	y = cp->y + 1;
	while (y < cp->sat->y + cp->sat->h)
	{
		step = (float) (y - cp->sat->y) / cp->sat->h;
		c1 = ft_color_lerp(C_WHITE, C_BLACK, step);
		c2 = ft_color_lerp(cp->hue_cursor->color, C_BLACK, step);
		x = cp->sat->x + 1;
		while (x < cp->sat->x + cp->sat->w)
		{
			ft_draw_pixel(img, x, y, ft_color_lerp(c1, c2, (float)(x - cp->sat->x) / cp->sat->w));
			x++;
			if (x == cp->sat_cursor->x && y == cp->sat_cursor->y)
				cp->sat_cursor->color = ft_color_lerp(c1, c2, (float)(x - cp->sat->x) / cp->sat->w);
		}
		y++;
	}
	ft_draw_circle(img, cp->sat_cursor->x, cp->sat_cursor->y, C_WHITE);
}

void	ft_color_picker_draw(t_image *img, t_color_picker *cp)
{
	ft_color_picker_hue_draw(img, cp);
	ft_color_picker_sat_draw(img, cp);
}

int	ft_is_inside_rectangle(t_rectangle *rec, int x, int y)
{
	return (rec->x < x && x < rec->x + rec->w
			&& rec->y < y && y < rec->y + rec->h);
}

int	ft_color_picker_focused(t_color_picker *cp, int x, int y)
{
	if (ft_is_inside_rectangle(cp->hue, x, y))
	{
		cp->hue_cursor->y = y;
		return (1);
	}
	else if (ft_is_inside_rectangle(cp->sat, x, y))
	{
		cp->sat_cursor->x = x;
		cp->sat_cursor->y = y;
		return (2);
	}
	return (0);
}

t_color_picker	*ft_color_picker_init(int x, int y)
{
	t_color_picker	*cp;

	cp = (t_color_picker *)malloc(sizeof(t_color_picker));
	cp->x = x;
	cp->y = y;
	cp->visible = TRUE;
	cp->sat = ft_rectangle_init(cp->x, cp->y, 300, 300);
	cp->sat_cursor= ft_point_init(cp->sat->x + 1, cp->sat->y + 1, 0, C_WHITE);

	cp->hue = ft_rectangle_init(cp->sat->x + cp->sat->w + 20, cp->sat->y, MENU_W * 0.1, cp->sat->h);
	cp->hue_cursor = ft_point_init(cp->hue->x, cp->hue->y + 1 /2, 0, C_WHITE);
	return (cp);
}
