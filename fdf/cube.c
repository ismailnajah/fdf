/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:14:20 by inajah            #+#    #+#             */
/*   Updated: 2024/11/30 11:29:01 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	cube_init(t_point *cube)
{
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
}

void	cube_draw(t_image *img, t_point *cube)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		draw_line(img, cube[i], cube[(i + 1) % 4], 1);
		i++;
	}
	draw_line(img, cube[0], cube[3], 1);
	draw_line(img, cube[0], cube[4], 1);
	draw_line(img, cube[7], cube[3], 1);
	draw_line(img, cube[4], cube[7], 1);
	draw_line(img, cube[4], cube[5], 1);
	draw_line(img, cube[5], cube[1], 1);
}

void	draw_cube_view(t_image *img, t_vars *vars)
{
	int				i;
	t_point			cube[8];
	static t_camera	cube_camera;

	cube_camera.option[ANGLE_X] = DEFAULT_ANGLE_X;
	cube_camera.option[ANGLE_Y] = DEFAULT_ANGLE_Y;
	cube_camera.option[ANGLE_Z] = DEFAULT_ANGLE_Z;
	cube_init(cube);
	i = 0;
	while (i < 8)
	{
		rotate_xyz_point(cube + i, vars->cube + i, &cube_camera);
		vars->cube[i].x = vars->cube[i].x * img->w * 0.5 + img->w / 2;
		vars->cube[i].y = vars->cube[i].y * img->w * 0.5 + img->h / 2;
		vars->cube[i].color = C_WHITE;
		i++;
	}
	cube_draw(img, vars->cube);
}

int	is_cube_clicked(int x, int y, t_vars *vars)
{
	t_point	*cube;

	if (x == -1 && y == -1)
		return (DEFAULT_VIEW);
	x = x - (WIN_W - vars->layout->cube_view->w);
	cube = vars->cube;
	if (cube[4].x < x && x < cube[1].x && cube[5].y < y && y < cube[0].y)
		return (TOP_VIEW);
	if (cube[7].x < x && x < cube[3].x && cube[0].y < y && y < cube[3].y)
		return (FRONT_VIEW);
	if (cube[3].x < x && x < cube[2].x && cube[0].y < y && y < cube[3].y)
		return (SIDE_VIEW);
	return (0);
}
