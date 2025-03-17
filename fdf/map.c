/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:30:01 by inajah            #+#    #+#             */
/*   Updated: 2024/11/30 11:56:23 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	map_realloc_points(t_map *map)
{
	t_point	*points;
	int		i;

	points = (t_point *)malloc((map->w * map->h) * sizeof(t_point));
	if (!points)
		return (FAILURE);
	i = 0;
	while (i < map->w * (map->h - 1))
	{
		points[i] = map->points[i];
		i++;
	}
	free(map->points);
	map->points = points;
	return (SUCCESS);
}

t_map	*map_init(int w, int h)
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->w = w;
	map->h = h;
	if (w == 0 || h == 0)
		map->points = NULL;
	else
	{
		map->points = (t_point *)malloc((w * h) * sizeof(t_point));
		if (!map->points)
			return (ft_abort(map));
	}
	return (map);
}

void	*map_free(t_map *map)
{
	free(map->points);
	map->points = NULL;
	free(map);
	return (NULL);
}

void	get_min_max_z(t_map *map, int *min, int *max)
{
	int	i;

	*max = map->points[0].z;
	*min = map->points[0].z;
	i = 0;
	while (i < map->h * map->w)
	{
		if (map->points[i].z > *max)
			*max = map->points[i].z;
		else if (map->points[i].z < *min)
			*min = map->points[i].z;
		i++;
	}
}

void	normalize_z(t_map *map)
{
	int	i;
	int	min;
	int	max;
	int	fact;

	get_min_max_z(map, &min, &max);
	i = 0;
	fact = max;
	if (max != min)
		fact = max - min;
	while (i < map->h * map->w && fact != 0)
	{
		map->points[i].z = (float)(map->points[i].z - min) / fact - 0.5;
		i++;
	}
}
