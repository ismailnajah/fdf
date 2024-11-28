/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:32:09 by inajah            #+#    #+#             */
/*   Updated: 2024/11/28 18:05:27 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_scale_z(t_map *map, float z_off)
{
	int		i;
	float	min;
	float	max;

	min = map->points[0].z;
	max = map->points[0].z;
	i = 0;
	while (i < map->w * map->h && z_off != 0.0f)
	{
		map->points[i].z /= z_off;
		if (max < map->points[i].z)
			max = map->points[i].z;
		if (min > map->points[i].z)
			min = map->points[i].z;
		i++;
	}
	map->min_z = min + 0.5f;
	map->max_z = max + 0.5f;
}

int	ft_in_image(t_image *img, t_point a)
{
	return (0 <= a.x && a.x < img->w
		&& 0 <= a.y && a.y < img->h);
}

float	ft_point_distance(t_point a, t_point b)
{
	return (sqrt((b.x - a.x) * (b.x - a.x) \
				+ (b.y - a.y) * (b.y - a.y)));
}

unsigned int	ft_get_point_color(t_vars *vars, t_point *p)
{
	unsigned int	lp_color;
	unsigned int	hp_color;
	float			min;
	float			max;

	lp_color = vars->low_p->color;
	hp_color = vars->high_p->color;
	min = vars->map->min_z;
	max = vars->map->max_z;
	if (min != max)
		return (ft_color_lerp(lp_color, hp_color,
				((p->z + 0.5f) - min) / (max - min)));
	else
		return (p->color);
}
