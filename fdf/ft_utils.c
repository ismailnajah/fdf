/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:07:50 by inajah            #+#    #+#             */
/*   Updated: 2024/11/22 17:42:10 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_view_change(int state, t_vars *vars)
{
	static int	animation_state;
	int			view;
	t_setting	view_s;
	t_setting	*s;

	if (state)
		animation_state = state;
	if (animation_state == STOP_ANIMATION)
		return ;
	s = vars->setting;
	if (animation_state == RESET_ANIMATION)
		view_s = ft_setting_default();
	else if (animation_state == UPDATE_ANIMATION)
	{
		view = ft_is_cube_clicked(vars->mouse_x, vars->mouse_y, vars);
		if (!view)
			return ;
		view_s = ft_setting_of_view(view, s);
	}
	ft_setting_animate(s, &view_s);
	if (s->angleX == view_s.angleX && s->angleY == view_s.angleY
		&& s->angleZ == view_s.angleZ && s->scale == view_s.scale
		&& s->x_off == view_s.x_off && s->y_off == view_s.y_off
		&& s->z_off == view_s.z_off)
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
