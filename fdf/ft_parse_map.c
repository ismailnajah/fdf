/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 08:18:29 by inajah            #+#    #+#             */
/*   Updated: 2024/11/30 11:38:47 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_parse_map_error(t_map *map, int diff)
{
	ft_printf(RED"[ ERROR ] "RESET);
	ft_printf("Line %d is too ", map->h);
	if (diff < 0)
		ft_printf("short.\n");
	else
		ft_printf("long.\n");
	return (FAILURE);
}

void	ft_parse_point(t_map *map, int i, int j, char *point_str)
{
	char	**words;
	int		w;

	w = (map->w != 1) * (map->w - 1) + 1 * (map->w == 1);
	map->points[j * map->w + i].x = ((float)i / w - 0.5f);
	map->points[j * map->w + i].y = ((float)j / w - 0.5f);
	map->points[j * map->w + i].z = 0;
	map->points[j * map->w + i].color = C_WHITE;
	words = ft_split(point_str, ',');
	if (!words)
		return ;
	map->points[j * map->w + i].z = ft_atoi(words[0]);
	map->points[j * map->w + i].color = ft_color_parse(words[1]);
	words = ft_split_free(words);
}

int	ft_parse_line(t_map *map, char *line, int j)
{
	static int	old_w = -1;
	char		**words;
	int			w;
	int			i;

	words = ft_split(line, ' ');
	if (!words)
		return (FAILURE);
	w = ft_split_count(words);
	if (old_w != -1 && w != old_w)
		return (ft_split_free(words), ft_parse_map_error(map, w - old_w));
	old_w = w;
	map->w = w;
	if (!ft_map_realloc_points(map))
		return (ft_print_error(ERR_MALLOC), ft_split_free(words), FAILURE);
	i = 0;
	while (words[i] && words[i][0] != '\n')
	{
		ft_parse_point(map, i, j, words[i]);
		i++;
	}
	ft_split_free(words);
	return (SUCCESS);
}

int	ft_parse_map(int fd, t_map *map)
{
	char	*line;
	int		j;
	int		ret;

	line = get_next_line(fd);
	if (!line)
		return (ft_print_error(ERR_EMPTY_FILE), FAILURE);
	j = 0;
	while (line)
	{
		map->h += 1;
		ret = ft_parse_line(map, line, j);
		free(line);
		if (!ret)
		{
			get_next_line(FREE_GNL_BUFFER);
			return (ft_print_error(ERR_PARSE));
		}
		line = get_next_line(fd);
		j++;
	}
	return (SUCCESS);
}

t_map	*ft_get_map_from_file(char *path)
{
	int		fd;
	t_map	*map;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (ft_print_error(ERR_FILE), NULL);
	ft_printf(GREEN"[ INFO  ]"RESET" Parsing the map...\n");
	map = ft_map_init(0, 0);
	if (!map)
	{
		close(fd);
		return (ft_print_error(ERR_MALLOC), NULL);
	}
	if (!ft_parse_map(fd, map))
	{
		close(fd);
		return (ft_map_free(map), NULL);
	}
	ft_normalize_z(map);
	close(fd);
	ft_printf(GREEN"[ INFO  ] "RESET"Parsing done.\n");
	ft_printf(GREEN"[ INFO  ] "RESET"Map %s ( %d x %d ) loaded.\n",
		basename(path), map->w, map->h);
	return (map);
}
