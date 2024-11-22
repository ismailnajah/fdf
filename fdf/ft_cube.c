/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cube.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:14:20 by inajah            #+#    #+#             */
/*   Updated: 2024/11/22 15:17:32 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_draw_cube_view(t_image *img, t_vars *vars)
{
	t_point cube[8];
	t_setting *cube_setting;

	cube_setting = ft_setting_init();

	cube[0].x = -0.5f;
	cube[0].y = 0.5f;
	cube[0].z = 0.5f;
	cube[1].x = 0.5f;
	cube[1].y = 0.5f;
	cube[1].z = 0.5f;
	cube[2].x = 0.5f;
	cube[2].y = 0.5f;
	cube[2].z = -0.5f;
	cube[3].x = -0.5f;
	cube[3].y = 0.5f;
	cube[3].z = -0.5f;
	cube[4].x = -0.5f;
	cube[4].y = -0.5f;
	cube[4].z = 0.5f;
	cube[5].x = 0.5f;
	cube[5].y = -0.5f;
	cube[5].z = 0.5f;
	cube[6].x = 0.5f;
	cube[6].y = -0.5f;
	cube[6].z = -0.5f;
	cube[7].x = -0.5f;
	cube[7].y = -0.5f;
	cube[7].z = -0.5f;

	for(int i=0; i< 8; i++)
	{
		ft_rotateXYZ_point(cube + i, vars->cube + i, cube_setting);
		vars->cube[i].x = vars->cube[i].x * img->w * 0.5 + img->w / 2;
		vars->cube[i].y = vars->cube[i].y * img->w * 0.5 + img->h / 2;
		vars->cube[i].color = C_WHITE;
	}
	// side view
	for(int i = 0; i < 4; i++)
	{
		ft_draw_line(img, vars->cube[i % 4], vars->cube[(i + 1) % 4]);
	}
	ft_draw_line(img, vars->cube[0], vars->cube[3]);
	ft_draw_line(img, vars->cube[0], vars->cube[4]);
	ft_draw_line(img, vars->cube[7], vars->cube[3]);
	ft_draw_line(img, vars->cube[4], vars->cube[7]);
	// top view
	ft_draw_line(img, vars->cube[4], vars->cube[5]);
	ft_draw_line(img, vars->cube[5], vars->cube[1]);
	free(cube_setting);
}

int	ft_is_cube_clicked(int x, int y, t_vars *vars)
{
	t_point *cube;

	if (x == -1 && y == -1)
		return (DEFAULT_VIEW);
	x = x - (WIN_W - vars->layout->cube_view->w);//the cube in top right corner.
	cube = vars->cube;
	if (cube[4].x < x && x < cube[1].x && cube[5].y < y && y < cube[0].y)
		return (TOP_VIEW);
	if (cube[7].x < x && x < cube[3].x && cube[0].y < y && y < cube[3].y)
		return (FRONT_VIEW);
	if (cube[3].x < x && x < cube[2].x && cube[0].y < y && y < cube[3].y)
		return (SIDE_VIEW);
	return (0); 
}
