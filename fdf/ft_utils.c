/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:07:50 by inajah            #+#    #+#             */
/*   Updated: 2024/11/24 21:40:59 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_camera_compare(t_camera *a, t_camera *b)
{
	int i;

	i = 0;
	while (i < OPTION_COUNT - 2)// do not include scale and z_off
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

unsigned int	ft_color_lerp(unsigned int c1, unsigned int c2, float t)
{
	int	r;
	int	g;
	int	b;

	r = get_r(c1) + t * (get_r(c2) - get_r(c1));
	g = get_g(c1) + t * (get_g(c2) - get_g(c1));
	b = get_b(c1) + t * (get_b(c2) - get_b(c1));
	return (create_trgb(0, r, g, b));
}

void	ft_scale_z(t_map *map, float z_off)
{
	int		i;

	i = 0;
	while (i < map->w * map->h && z_off != 0.0f)
	{
		map->points[i].z /= z_off;
		i++;
	}
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
	int i;
	int min;
	int max;

	ft_get_min_max_z(map, &min, &max);
	i = 0;
	while (i < map->h * map->w && max != min)
	{
		map->points[i].z = (((float)(map->points[i].z - min) / (float)(max - min)) - 0.5f) / 4;
		i++;
	}
}
