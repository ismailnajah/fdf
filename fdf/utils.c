/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:07:50 by inajah            #+#    #+#             */
/*   Updated: 2025/01/26 09:50:55 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	print_error(int err, char *path)
{
	printf(RED"[ ERROR ] "RESET);
	if (err == ERR_FILE)
	{
		printf("could not open %s: ", path);
		perror("");
	}
	if (err == ERR_IS_DIR)
		printf("could not open %s: %s.\n", path, strerror(EISDIR));
	if (err == ERR_MAP)
		printf("Invalid map.\n");
	if (err == ERR_PARSE)
		printf("Parsing error occured.\n");
	if (err == ERR_MALLOC)
		printf("Unable to allocate resources.\n");
	if (err == ERR_EMPTY_FILE)
		printf("The map is empty.\n");
	if (err == ERR_FILE_EXTENSION)
	{
		printf("Bad file extension.\n");
		printf("    Usage: ./fdf filename.fdf\n");
	}
	return (FAILURE);
}

int	camera_compare(t_camera *a, t_camera *b)
{
	int	i;

	i = 0;
	while (i < SCALE)
	{
		if (a->option[i] != b->option[i])
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void	view_change(int state, t_vars *vars)
{
	static int	animation_state;
	int			view;
	t_camera	view_c;
	t_camera	*c;

	if (state)
		animation_state = state;
	if (animation_state == STOP_ANIMATION)
		return ;
	c = vars->camera;
	if (animation_state == RESET_ANIMATION)
		view_c = camera_default();
	else if (animation_state == UPDATE_ANIMATION)
	{
		view = is_cube_clicked(vars->mouse->x, vars->mouse->y, vars);
		if (!view)
			return ;
		view_c = camera_of_view(view, c);
	}
	camera_update(c, &view_c);
	if (camera_compare(c, &view_c))
		animation_state = STOP_ANIMATION;
}

unsigned int	hex_to_int(char *hex)
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

int	is_valid_file(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY | O_DIRECTORY);
	if (fd > 0)
	{
		close(fd);
		return (print_error(ERR_IS_DIR, path));
	}
	if (strncmp(path + strlen(path) - 4, ".fdf", 4) != 0)
		return (print_error(ERR_FILE_EXTENSION, path));
	return (SUCCESS);
}
