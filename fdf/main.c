/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:26:50 by inajah            #+#    #+#             */
/*   Updated: 2024/11/13 18:36:55 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//TODO: implement map parser that check each line.
// 		and determine if the map is valid or not
// 		a valid map must follow this rules:
// 			- only contains space and digits.
// 			- all the lines have the same number of values.

typedef struct s_map
{
	int width;
	int height;
	int	*values;
}	t_map;

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
		printf("Invalid map\n");
	else
		printf("width: %d | height: %d\n", w, h);

	return 1;
}

int	main(int ac, char **av)
{

	if (ac != 2)
		return (1);
	ft_parse_map(av[1]);
	return (0);
}
