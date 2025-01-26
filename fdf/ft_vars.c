/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:30:04 by inajah            #+#    #+#             */
/*   Updated: 2025/01/26 09:35:57 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_is_camera_changed(t_camera *c, t_camera *old)
{
	int	changed;
	int	i;

	i = 0;
	changed = 0;
	while (i < OPTION_COUNT)
	{
		if (c->option[i] != old->option[i])
		{
			old->option[i] = c->option[i];
			changed++;
		}
		i++;
	}
	return (changed > 0);
}

int	ft_is_vars_changed(t_vars	*vars)
{
	static unsigned int	lp_color;
	static unsigned int	hp_color;
	static t_camera		old;
	int					changed;

	changed = 0;
	if (vars->low_p->color != lp_color)
	{
		lp_color = vars->low_p->color;
		changed++;
	}
	if (vars->high_p->color != hp_color)
	{
		hp_color = vars->high_p->color;
		changed++;
	}
	return (changed || ft_is_camera_changed(vars->camera, &old));
}

int	ft_vars_free(t_vars *vars)
{
	if (vars->cube)
		free(vars->cube);
	if (vars->camera)
		ft_camera_free(vars->camera);
	if (vars->layout)
		ft_layout_free(vars->mlx, vars->layout);
	if (vars->map)
		ft_map_free(vars->map);
	if (vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	if (vars->mlx)
		mlx_destroy_display(vars->mlx);
	ft_color_picker_free(vars->color_picker);
	free(vars->labels);
	ft_color_option_free(vars->low_p);
	ft_color_option_free(vars->high_p);
	free(vars->mlx);
	return (0);
}

int	ft_vars_init(t_vars *vars, char *map_path)
{
	vars->map = ft_get_map_from_file(map_path);
	if (!vars->map)
		return (FAILURE);
	vars->mlx = mlx_init();
	if (!vars->mlx)
		return (ft_vars_free(vars), FAILURE);
	vars->win = mlx_new_window(vars->mlx, WIN_W, WIN_H, "Fil de Fer");
	vars->layout = ft_layout_init(vars->mlx);
	vars->camera = ft_camera_init();
	vars->color_picker = ft_color_picker_init(10, MENU_H * 0.7);
	vars->cube = (t_point *)malloc(8 * sizeof(t_point));
	vars->low_p = ft_color_option_init(vars->color_picker);
	vars->high_p = ft_color_option_init(vars->color_picker);
	vars->labels = ft_labels_init();
	vars->mouse = ft_mouse_init();
	if (!vars->win || !vars->layout || !vars->camera || !vars->cube
		|| !vars->low_p || !vars->high_p || !vars->labels || !vars->mouse)
		return (ft_vars_free(vars), FAILURE);
	return (SUCCESS);
}
