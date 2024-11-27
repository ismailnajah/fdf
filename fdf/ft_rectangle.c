/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rectangle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:23:40 by inajah            #+#    #+#             */
/*   Updated: 2024/11/27 17:12:47 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

int	ft_is_inside_rectangle(t_rectangle *rec, int x, int y)
{
	return (rec->x < x && x < rec->x + rec->w
		&& rec->y < y && y < rec->y + rec->h);
}

void	ft_rectangle_draw(t_image *img, t_rectangle *rec, unsigned int color)
{
	t_point	a;

	a.x = rec->x;
	a.y = rec->y;
	a.color = color;
	ft_border_draw(img, a, rec->w, rec->h);
}

t_rectangle	*ft_rectangle_init(int x, int y, int w, int h)
{
	t_rectangle	*rec;

	rec = (t_rectangle *)malloc(sizeof(t_rectangle));
	if (!rec)
		return (NULL);
	rec->x = x;
	rec->y = y;
	rec->w = w;
	rec->h = h;
	return (rec);
}
