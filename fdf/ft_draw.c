/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:12:32 by inajah            #+#    #+#             */
/*   Updated: 2024/11/23 22:58:48 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_draw_main_view_v2(t_vars *vars);

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
	t_point		b;
	t_point		proj;
	t_map		*map;
	t_setting	*s;

	map = vars->map;
	s = vars->setting;
	ft_rotate_xyz_point(map->points + (j * map->w + i), &proj, s);
	ft_point_scale(&a, &proj, s);
	if (i + 1 < map->w)
	{
		ft_rotate_xyz_point(map->points + (j * map->w + i + 1), &proj, s);
		ft_point_scale(&b, &proj, s);
		ft_draw_line(img, a, b);
	}
	if (j + 1 < map->h)
	{
		ft_rotate_xyz_point(map->points + ((j + 1) * map->w + i), &proj, s);
		ft_point_scale(&b, &proj, s);
		ft_draw_line(img, a, b);
	}
}

void	ft_draw_main_view(t_vars *vars)
{
	ft_draw_main_view_v2(vars);
/*
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
*/
}

void	ft_draw_main_view_test(t_vars *vars, t_point start, t_point end)
{
	int	i;
	int	j;

	if (start.y == end.y)
	{
		j = start.y;
		while (0 <= j && j < vars->map->h)
		{
			i = start.x;
			while (0 <= i && i < vars->map->w)
			{
				ft_draw_cell(vars->layout->main, vars, i, j);
				i += (1 - 2 * (start.x == vars->map->w - 1));
			}
			j += (1 - 2 * (start.y == vars->map->h - 1));
		}
	}
	else
	{	
		j = start.x;
		while (0 <= j && j < vars->map->w)
		{
			i = start.y;
			while (0 <= i && i < vars->map->h)
			{
				ft_draw_cell(vars->layout->main, vars, j, i);
				i += (1 - 2 * (start.y == vars->map->h - 1));
			}
			j += (1 - 2 * (start.x == vars->map->w - 1));
		}
	}
}

float	ft_slope(t_point *a, t_point *b)
{
	if (a->x == b->x)
		return (0);
	return ((b->y - a->y) / (b->x - a->x));
}

// this is the order of the corner points of our map
// start->a ------ b
//        |   -->  |
//        |   -->  |
//        d ------ c <-end

int 	ft_point_min_index(t_point *p, int cmp_x)
{
	int i;
	int min_index;
	float min_value;

	i = 0;
	min_index = 0;
	min_value = 999999;
	while (i < 4)
	{
		if (p[i].x < min_value && cmp_x)
		{
			min_value = p[i].x;
			min_index = i;
		}
		if (p[i].y < min_value && !cmp_x)
		{
			min_value = p[i].y;
			min_index = i;
		}
		i++;
	}
	return (min_index);
}

void	ft_draw_main_view_v2(t_vars *vars)
{
	t_point corner[4];
	t_point	index[4];
   	t_point	start;
	t_point	end;
	t_map	*map;
	int		i;

	map = vars->map;
	index[0].x = 0;//a
	index[0].y = 0;//a
	index[1].x = map->w - 1;//b
	index[1].y = 0;//b
	index[2].x = map->w - 1;//c
	index[2].y = map->h - 1;//c
	index[3].x = 0;//d
	index[3].y = map->h - 1;//d
	i = 0;
	while (i < 4)
	{
		ft_rotate_xyz_point(map->points + (int)(map->w * index[i].y + index[i].x), &corner[i], vars->setting);
		ft_point_scale(&corner[i], &corner[i], vars->setting);
		i++;
	}
	int start_index = ft_point_min_index(corner, 1);
	start = index[start_index];
	if (start_index == 0)
	{
		if (corner[1].y <= corner[3].y)
			end = index[1];
		else
			end = index[3];
	}
	else if (start_index == 1)
	{	
		if (corner[0].y <= corner[2].y)
			end = index[0];
		else
			end = index[2];

	}
	else if (start_index == 2)
	{
		if (corner[1].y <= corner[3].y)
			end = index[1];
		else
			end = index[3];
	}
	else
	{	
		if (corner[2].y <= corner[0].y)
			end = index[2];
		else
			end = index[0];
	}
	ft_draw_main_view_test(vars, start, end);
}
