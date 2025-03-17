/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:31:51 by inajah            #+#    #+#             */
/*   Updated: 2025/03/17 13:32:50 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_circle_pixels(t_image *img, t_point *c, int x, int y)
{
	draw_pixel(img, c->x + x, c->y + y, c->color);
	draw_pixel(img, c->x + y, c->y + x, c->color);
	draw_pixel(img, c->x - y, c->y + x, c->color);
	draw_pixel(img, c->x - x, c->y + y, c->color);
	draw_pixel(img, c->x - x, c->y - y, c->color);
	draw_pixel(img, c->x - y, c->y - x, c->color);
	draw_pixel(img, c->x + y, c->y - x, c->color);
	draw_pixel(img, c->x + x, c->y - y, c->color);
}

void	circle_draw(t_image *img, t_point center)
{
	int		radius;
	int		x;
	int		y;
	int		radius_error;

	radius = 10;
	x = radius;
	y = 0;
	radius_error = 1 - radius;
	center.color = C_WHITE;
	while (x >= y)
	{
		draw_circle_pixels(img, &center, x, y);
		y++;
		if (radius_error < 0)
			radius_error += 2 * y + 1;
		else
		{
			x--;
			radius_error += 2 * (y - x + 1);
		}
	}
}
