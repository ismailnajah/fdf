/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:29:06 by inajah            #+#    #+#             */
/*   Updated: 2024/11/27 15:42:50 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_color_picker_focused(t_color_picker *cp, int x, int y)
{
	if (ft_is_inside_rectangle(cp->hue, x, y))
	{
		cp->hue_cursor->y = y;
		return (CP_HUE);
	}
	else if (ft_is_inside_rectangle(cp->sat, x, y))
	{
		cp->sat_cursor->x = x;
		cp->sat_cursor->y = y;
		return (CP_SAT);
	}
	return (FALSE);
}

unsigned int	next_color(unsigned int color)
{
	int	step;
	int	r;
	int	g;
	int	b;

	step = 5;
	r = get_r(color);
	g = get_g(color);
	b = get_b(color);
	r += step * (r != 255 && g == 0 && b == 255);
	r -= step * (r != 0 && g == 255 && b == 0);
	g += step * (r == 255 && g != 255 && b == 0);
	g -= step * (r == 0 && g != 0 && b == 255);
	b += step * (r == 0 && g == 255 && b != 255);
	b -= step * (r == 255 && g == 0 && b != 0);
	return (create_trgb(0, r, g, b));
}

unsigned int	ft_color_lerp(unsigned int c1, unsigned int c2, float t)
{
	int	r;
	int	g;
	int	b;

	r = get_r(c1) + t * (get_r(c2) - get_r(c1));
	g = get_g(c1) + t * (get_g(c2) - get_g(c1));
	b = get_b(c1) + t * (get_b(c2) - get_b(c1));
	return (create_trgb(0, r, g, b));
}
