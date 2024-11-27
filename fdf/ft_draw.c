/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:12:32 by inajah            #+#    #+#             */
/*   Updated: 2024/11/27 16:45:16 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_draw_pixel(t_image *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= img->w || y >= img->h)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

void	ft_draw_line(t_image *img, t_point a, t_point b)
{
	float			y;
	float			x;

	if (ft_point_sort(&a, &b))
	{
		y = a.y;
		while (y <= b.y && a.y != b.y)
		{
			x = a.x + (y - a.y) * ((b.x - a.x) / (b.y - a.y));
			ft_draw_pixel(img, x, y,
				ft_color_lerp(a.color, b.color, (float)y / b.y));
			y += 1;
		}
	}
	else
	{
		x = a.x;
		while (x <= b.x && a.x != b.x)
		{
			y = a.y + (x - a.x) * ((b.y - a.y) / (b.x - a.x));
			ft_draw_pixel(img, x, y,
				ft_color_lerp(a.color, b.color, (float)x / b.x));
			x += 1;
		}
	}
}

unsigned int	ft_get_point_color(t_vars *vars, float z)
{
	unsigned int	lp_color;
	unsigned int	hp_color;
	float			min;
	float			max;

	lp_color = vars->low_p->color;
	hp_color = vars->high_p->color;
	min = vars->map->minZ;
	max = vars->map->maxZ;
	return (ft_color_lerp(lp_color, hp_color,
			((z + 0.5f) - min) / (max - min)));
}

void	ft_draw_cell(t_image *img, t_vars *vars, int i, int j)
{
	t_point		a;
	t_point		proj;
	t_point		*o;
	t_map		*map;
	t_camera	*c;

	map = vars->map;
	c = vars->camera;
	o = &map->points[j * map->w + i];
	if (vars->low_p->focused || vars->high_p->focused)
		o->color = ft_get_point_color(vars, o->z);
	ft_rotate_xyz_point(map->points + (j * map->w + i), &proj, c);
	ft_point_scale(&a, &proj, c);
	if (i + 1 < map->w)
	{
		ft_rotate_xyz_point(map->points + (j * map->w + i + 1), &proj, c);
		ft_point_scale(&proj, &proj, c);
		ft_draw_line(img, a, proj);
	}
	if (j + 1 < map->h)
	{
		ft_rotate_xyz_point(map->points + ((j + 1) * map->w + i), &proj, c);
		ft_point_scale(&proj, &proj, c);
		ft_draw_line(img, a, proj);
	}
}

void	ft_draw_main_view(t_vars *vars)
{
	int	i;
	int	j;

	j = 0;
	while (j < vars->map->h)
	{
		i = 0;
		while (i < vars->map->w)
		{
			ft_draw_cell(vars->layout->main, vars, i, j);
			i++;
		}
		j++;
	}
}
