/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:12:32 by inajah            #+#    #+#             */
/*   Updated: 2024/11/26 17:28:11 by inajah           ###   ########.fr       */
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
	o->color = ft_color_lerp(vars->lp_color, vars->hp_color, (((o->z + 0.5f) - map->minZ) / (map->maxZ - map->minZ)));
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
