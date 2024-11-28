/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:30:01 by inajah            #+#    #+#             */
/*   Updated: 2024/11/28 18:15:41 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_map_realloc_points(t_map *map)
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

t_map	*ft_map_init(int w, int h)
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

void	*ft_map_free(t_map *map)
{
	free(map->points);
	map->points = NULL;
	free(map);
	return (NULL);
}

void	ft_get_min_max_z(t_map *map, int *min, int *max)
{
	int	i;

	*max = map->points[0].z;
	*min = map->points[0].z;
	i = 0;
	while (i < map->h * map->w)
	{
		if (map->points[i].z > *max)
			*max = map->points[i].z;
		if (map->points[i].z < *min)
			*min = map->points[i].z;
		i++;
	}
}
