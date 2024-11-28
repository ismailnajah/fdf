/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:07:50 by inajah            #+#    #+#             */
/*   Updated: 2024/11/28 15:02:51 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_camera_compare(t_camera *a, t_camera *b)
{
	int	i;

	i = 0;
	while (i < OPTION_COUNT - 2)
	{
		if (a->option[i] != b->option[i])
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void	ft_view_change(int state, t_vars *vars)
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
		view_c = ft_camera_default();
	else if (animation_state == UPDATE_ANIMATION)
	{
		view = ft_is_cube_clicked(vars->mouse_x, vars->mouse_y, vars);
		if (!view)
			return ;
		view_c = ft_camera_of_view(view, c);
	}
	ft_camera_animate(c, &view_c);
	if (ft_camera_compare(c, &view_c))
		animation_state = STOP_ANIMATION;
}

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

void	ft_normalize_z(t_map *map)
{
	int	i;
	int	min;
	int	max;
	int	fact;

	ft_get_min_max_z(map, &min, &max);
	i = 0;
	fact = max;
	if (max != min)
		fact = max - min;
	while (i < map->h * map->w && max != min)
	{
		map->points[i].z = (map->points[i].z - min) / fact - 0.5f;
		i++;
	}
	if (fact)
	{
		map->min_z = (float)min / fact;
		map->max_z = (float)max / fact;
	}
	else
	{
		map->min_z = 0;
		map->max_z = 0;
	}
}
