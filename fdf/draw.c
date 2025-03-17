/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:12:32 by inajah            #+#    #+#             */
/*   Updated: 2024/11/30 11:31:48 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_pixel(t_image *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= img->w || y >= img->h)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

void	draw_line(t_image *img, t_point start, t_point end, int fact)
{
	t_point	d;
	t_point	p;
	int		steps;
	int		dist;

	if (!in_image(img, start) && !in_image(img, end))
		return ;
	d.x = end.x - start.x;
	d.y = end.y - start.y;
	dist = point_distance(start, end);
	steps = dist;
	d.x /= steps;
	d.y /= steps;
	p.x = start.x;
	p.y = start.y;
	fact = abs(fact);
	while (steps > 0)
	{
		p.color = color_lerp(start.color, end.color,
				(float)(dist - steps) / dist);
		draw_pixel(img, p.x, p.y, p.color);
		p.x += d.x * fact;
		p.y += d.y * fact;
		steps -= fact;
	}
}

void	draw_projected_line(t_vars *vars, t_point a, int i, int j)
{
	t_point		p;
	t_point		proj;
	t_map		*map;
	t_image		*img;
	t_camera	*c;

	map = vars->map;
	img = vars->layout->main;
	c = vars->camera;
	point_copy(&p, map->points + (j * map->w + i));
	if (vars->low_p->focused || vars->high_p->focused)
		p.color = get_point_color(vars, &p);
	map->points[j * map->w + i].color = p.color;
	p.z = p.z * (c->option[Z_OFF] / DEFAULT_Z_OFF);
	rotate_xyz_point(&p, &proj, c);
	point_scale(&proj, &proj, c);
	if (point_distance(proj, a) < EPSI)
		draw_pixel(img, a.x, a.y, color_lerp(a.color, proj.color, 0.5));
	else
		draw_line(img, a, proj, 1 + vars->camera->option[DOT_FACT]);
}

void	draw_cell(t_vars *vars, int i, int j)
{
	t_point		p;
	t_point		proj;
	t_map		*map;
	t_camera	*c;

	map = vars->map;
	c = vars->camera;
	point_copy(&p, &map->points[j * map->w + i]);
	if (vars->low_p->focused || vars->high_p->focused)
		p.color = get_point_color(vars, &p);
	map->points[j * map->w + i].color = p.color;
	p.z = p.z * (c->option[Z_OFF] / DEFAULT_Z_OFF);
	rotate_xyz_point(&p, &proj, c);
	point_scale(&proj, &proj, c);
	if (i + 1 < map->w)
		draw_projected_line(vars, proj, i + 1, j);
	if (j + 1 < map->h)
		draw_projected_line(vars, proj, i, j + 1);
}

void	draw_main_view(t_vars *vars)
{
	int	i;
	int	j;

	j = 0;
	while (j < vars->map->h)
	{
		i = 0;
		while (i < vars->map->w)
		{
			draw_cell(vars, i, j);
			i++;
		}
		j++;
	}
}
