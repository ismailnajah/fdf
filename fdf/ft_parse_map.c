/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 08:18:29 by inajah            #+#    #+#             */
/*   Updated: 2024/11/16 10:21:05 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_get_map_resolution(char *path, int *w, int *h)
{
	char	prev;
	char	c;
	int		fd;
	int		old_w;

	fd = open(path, O_RDONLY);
	prev = ' ';
	old_w = -1;
	while(read(fd, &c, 1) > 0)
	{
		if (c == '\n')
		{
			if (old_w != -1 && old_w != *w)
				return (close(fd), 0);
			old_w = *w;
			*w = 0; 
			*h += 1;
		}
		else if (c != ' ' &&  (prev == ' ' || prev == '\n'))
			*w += 1;
		prev = c;
	}
	*w = old_w;
	return (close(fd), 1);
}

int	ft_parse_map(char *path)
{
	int w;
	int h;

	w = 0;
	h = 0;
	if (!ft_get_map_resolution(path, &w, &h))
		ft_printf("Invalid map\n");
	else
		ft_printf("width: %d | height: %d\n", w, h);

	return 1;
}


