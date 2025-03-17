/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:29:06 by inajah            #+#    #+#             */
/*   Updated: 2024/11/28 15:29:51 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

unsigned int	color_parse(char *color_str)
{
	if (!color_str)
		return (C_WHITE);
	if (color_str[0] != '0' || (color_str[1] != 'x' && color_str[1] != 'X'))
		return (C_WHITE);
	return (hex_to_int(color_str + 2));
}

void	color_option_focused(t_vars *vars, int x, int y)
{
	vars->low_p->focused = FALSE;
	vars->high_p->focused = FALSE;
	if (LP_COLOR_X < x && x < LP_COLOR_X + COLOR_W)
	{
		if (LP_COLOR_Y < y && y < LP_COLOR_Y + COLOR_W)
		{
			vars->low_p->focused = TRUE;
			point_copy(vars->color_picker->sat_cursor, vars->low_p->sat);
			point_copy(vars->color_picker->hue_cursor, vars->low_p->hue);
		}
		else if (HP_COLOR_Y < y && y < HP_COLOR_Y + COLOR_W)
		{
			vars->high_p->focused = TRUE;
			point_copy(vars->color_picker->sat_cursor, vars->high_p->sat);
			point_copy(vars->color_picker->hue_cursor, vars->high_p->hue);
		}
	}
}

int	color_picker_focused(t_color_picker *cp, int x, int y)
{
	if (is_inside_rect(cp->hue, x, y))
	{
		cp->hue_cursor->y = y;
		return (CP_HUE);
	}
	else if (is_inside_rect(cp->sat, x, y))
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

unsigned int	color_lerp(unsigned int c1, unsigned int c2, float t)
{
	int	r;
	int	g;
	int	b;

	r = get_r(c1) + t * (get_r(c2) - get_r(c1));
	g = get_g(c1) + t * (get_g(c2) - get_g(c1));
	b = get_b(c1) + t * (get_b(c2) - get_b(c1));
	return (create_trgb(0, r, g, b));
}
