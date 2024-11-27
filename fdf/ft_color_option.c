/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color_option.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:39:39 by inajah            #+#    #+#             */
/*   Updated: 2024/11/27 19:13:36 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	*ft_color_option_free(t_color_option *opt)
{
	if (!opt)
		return (NULL);
	free(opt->hue);
	free(opt->sat);
	free(opt);
	return (NULL);
}

t_color_option	*ft_color_option_init(t_color_picker *cp)
{
	t_color_option	*opt;

	if (!cp)
		return (NULL);
	opt = (t_color_option *)malloc(sizeof(t_color_option));
	if (!opt)
		return (NULL);
	opt->hue = ft_point_init(0, 0, 0, C_WHITE);
	opt->sat = ft_point_init(0, 0, 0, C_WHITE);
	opt->focused = FALSE;
	opt->color = cp->sat_cursor->color;
	if (!opt->hue || !opt->sat)
		return (ft_color_option_free(opt));
	ft_point_copy(opt->hue, cp->hue_cursor);
	ft_point_copy(opt->sat, cp->sat_cursor);
	return (opt);
}

void	ft_color_option_draw(t_image *img, t_point p, int w)
{
	int	x;
	int	y;

	y = p.y + 1;
	while (y < p.y + w)
	{
		x = p.x + 1;
		while (x < p.x + w)
		{
			ft_draw_pixel(img, x, y, p.color);
			x++;
		}
		y++;
	}
}
