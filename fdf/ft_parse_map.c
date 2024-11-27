/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 08:18:29 by inajah            #+#    #+#             */
/*   Updated: 2024/11/27 20:34:14 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_get_map_resolution(char *path, int *w, int *h)
{
	char	prev;
	char	c;
	int		fd;
	int		old_w;
	int		byte_read;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (FAILURE);
	prev = ' ';
	old_w = -1;
	byte_read = read(fd, &c, 1);
	if (byte_read < 0)
		return (close(fd), FAILURE);
	while (byte_read >= 0)
	{
		if (c == '\n' || byte_read == 0)
		{
			if (*w > 0)
				*h += 1;
			if (byte_read == 0)
				break;
			if (old_w != -1 && old_w != *w)
				return (close(fd), FAILURE);
			old_w = *w;
			*w = 0;
		}
		else if (c != ' ' && (prev == ' ' || prev == '\n'))
			*w += 1;
		prev = c;
		byte_read = read(fd, &c, 1);
		if (byte_read < 0)
			return (close(fd), FAILURE);
	}
	*w = old_w;
	return (close(fd), SUCCESS);
}

void	*ft_words_free(char **words)
{
	int	i;

	i = 0;
	if (!words)
		return (NULL);
	while (words[i])
	{
		free(words[i]);
		words[i] = NULL;
		i++;
	}
	free(words);
	return (NULL);
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
	words = ft_words_free(words);
}

int	ft_parse_line(t_map *map, char *line, int j)
{
	char	**words;
	int		i;

	words = ft_split(line, ' ');
	if (!words)
		return (ft_printf("[ ERROR ] unable to parse the map."), FAILURE);
	i = 0;
	while (words[i] && words[i][0] != '\n')
	{
		ft_parse_point(map, i, j, words[i]);
		i++;
	}
	ft_words_free(words);
	return (SUCCESS);
}

int	ft_parse_map(int fd, t_map *map)
{
	char	*line;
	int		j;
	int		ret;

	line = get_next_line(fd);
	if (!line)
		return (ft_printf("[ ERROR ] unable to parse the map.\n"), FAILURE);
	j = 0;
	while (line)
	{
		ret = ft_parse_line(map, line, j);
		free(line);
		if (!ret)
			return (FAILURE);
		line = get_next_line(fd);
		j++;
	}
	return (SUCCESS);
}

t_map	*ft_get_map_from_file(char *path)
{
	int		w;
	int		h;
	int		fd;
	t_map	*map;

	w = 0;
	h = 0;
	if (!ft_get_map_resolution(path, &w, &h))
		return (ft_printf("[ ERROR ] Invalid map.\n"), NULL);
	else
		ft_printf("[ INFO  ] Loading the map...\n");
	map = ft_map_init(w, h);
	if (!map)
		return (ft_printf("[ ERROR ] Failed to allocate the map.\n"), NULL);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (ft_printf("[ ERROR ]\n"), ft_map_free(map));
	if (!ft_parse_map(fd, map))
		return (ft_map_free(map), NULL);
	ft_normalize_z(map);
	close(fd);
	ft_printf("[ INFO  ] Loading done.\n");
	ft_printf(" ##  Map %s ##\n", path);
	ft_printf("\t- width:  %d\n\t- height: %d\n", map->w, map->h);
	return (map);
}
