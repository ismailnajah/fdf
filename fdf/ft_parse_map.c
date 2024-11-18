/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 08:18:29 by inajah            #+#    #+#             */
/*   Updated: 2024/11/18 15:53:05 by inajah           ###   ########.fr       */
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
//TODO: create a function that handles errors of opening a file.
//		errors: file does not exist or the path is a directory or low permissions.
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (FAILURE);
	prev = ' ';
	old_w = -1;
	byte_read = read(fd, &c, 1);
	if (byte_read < 0)
		return (close(fd), FAILURE);
	while(byte_read >= 0)
	{
		if (c == '\n' || byte_read == 0)
		{
			if (*w > 0)
				*h += 1;
			if (byte_read == 0)
				break ;
			if (old_w != -1 && old_w != *w)
				return (close(fd), FAILURE);
			old_w = *w;
			*w = 0; 
		}
		else if (c != ' ' &&  (prev == ' ' || prev == '\n'))
			*w += 1;
		prev = c;
		byte_read = read(fd, &c, 1);
		if (byte_read < 0)
			return (close(fd), FAILURE);
	}
	*w = old_w;
	return (close(fd), SUCCESS);
}

t_map	*ft_init_map(int w, int h)
{
	t_map	*map;

	map = (t_map*)malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->w = w;
	map->h = h;
	map->points = (t_point*)malloc((w * h) * sizeof(t_point));
	if (!map->points)
		return (ft_abort(map));
	return (map);
}

void	*ft_free_map(t_map *map)
{
	free(map->points);
	map->points = NULL;
	free(map);
	return (NULL);
}

void	*ft_free_words(char **words)
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

unsigned int	ft_hex_to_int(char *hex)
{
	unsigned int	color;
	int				i;
	char			c;
   
	color = 0;
	i = 0;
	while (hex[i] && hex[i] != '\n')
	{
		c = ft_toupper(hex[i]);
		if (ft_isdigit(c))
			color = color * 16 + c - '0';
		else if ('A' <= c && c <= 'F')
			color = color * 16 + 10 + c - 'A';
		else
			return (C_WHITE);
		i++;
	}
	return (color);
}

unsigned int	ft_parse_color(char *color_str)
{
	if (!color_str)
		return (C_WHITE);
	if (color_str[0] != '0' || (color_str[1] != 'x' && color_str[1] != 'X'))
		return (C_WHITE);
	return (ft_hex_to_int(color_str + 2));
}

void	ft_parse_point(t_map *map, int i, int j, char *point_str)
{
	char	**words;
	int		w;
	int		h;

	w = (map->w != 1) * (map->w - 1) + 1 * (map->w == 1);
	h = (map->h != 1) * (map->h - 1) + 1 * (map->h == 1);
	map->points[j * map->w + i].x = ((float)i / w - 0.5f);
	map->points[j * map->w + i].y = ((float)j / h - 0.5f);
	map->points[j * map->w + i].z = 0;
	map->points[j * map->w + i].color = C_WHITE;
	words = ft_split(point_str, ',');
	if (!words)
		return ;	
	map->points[j * map->w + i].z = ft_atoi(words[0]);
	map->points[j * map->w + i].color = ft_parse_color(words[1]);
	words = ft_free_words(words);
}

void	ft_get_min_max_z(t_map *map, int *min, int *max)
{
	int i;

	*max = INT_MIN;
	*min = INT_MAX;
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


int	ft_parse_map(int fd, t_map *map)
{
	int			i;
	int			j;
	char	*line;
	char 	**words;
	
	line = get_next_line(fd);
	if (!line)
		return (ft_printf("[ ERROR ] parsing error : could not read the line from file"), FAILURE);
	j = 0;
	while (line)
	{
		words = ft_split(line, ' ');
		free(line);
		if (!words)
			return (ft_printf("[ ERROR ] parsing error : could not split the line into words"), FAILURE);
		i = 0;
		while (words[i] && words[i][0] != '\n')
		{
			ft_parse_point(map, i, j, words[i]);
			i++;
		}
		words = ft_free_words(words);
		line = get_next_line(fd);
		j++;
	}
	return (SUCCESS);
}

void ft_debug_map(t_map *map)
{
	int i;
	int j;
	char *hash;
	t_point	p;

	hash = "----------------------------------------------------------";
	ft_printf(" %s (width:%d, height:%d) %s\n", hash, map->w, map->h, hash);
	j = 0;
	while (j < map->h)
	{
		i = 0;
		while (i < map->w)
		{
			p = map->points[j * map->w + i];
			printf("(%2.2f, %2.2f, %2.2f)%#X ", p.x, p.y, p.z, p.color);
			i++;
		}
		fflush(NULL);
		ft_printf("\n");
		j++;
	}
}

void	ft_normalize_z(t_map *map)
{
	int i;
	int min;
	int max;

	ft_get_min_max_z(map, &min, &max);
	i = 0;
	while (i < map->h * map->w && max != min)
	{
		map->points[i].z = ((float)(map->points[i].z - min) / (float)(max - min)) - 0.5f;
		i++;
	}
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
		ft_printf("[ INFO  ] Loading the map %s (width: %d | height: %d)\n", path, w, h);
	map = ft_init_map(w, h);
	if (!map)
	{
		ft_printf("[ ERROR ] Failed to allocate the map.");
		return (NULL);
	}
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (ft_printf("[ ERROR ] %s could not be opened: %s\n", path, strerror(errno)), ft_free_map(map));
	ft_parse_map(fd, map);
	ft_normalize_z(map);
	close(fd);
	ft_printf("[ INFO  ] Loading done.\n");
	return (map);
}
