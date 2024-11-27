/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:30:01 by inajah            #+#    #+#             */
/*   Updated: 2024/11/27 17:32:35 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map	*ft_map_init(int w, int h)
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->w = w;
	map->h = h;
	map->points = (t_point *)malloc((w * h) * sizeof(t_point));
	if (!map->points)
		return (ft_abort(map));
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
