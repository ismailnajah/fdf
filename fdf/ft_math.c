/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:22:52 by inajah            #+#    #+#             */
/*   Updated: 2024/11/21 10:18:10 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

# define PI 3.14159265358979311600

float	ft_cos(float new_angle)
{
	static int		flag;
	static float	angle;
	static float	cos_angle;

	//convert to radiant
	new_angle = (PI * new_angle) / 180;
	if (flag == 0)
	{
		flag = 1;
		cos_angle = 1;
	}
	if (1 && new_angle == angle)
		return (cos_angle);
	angle = new_angle;
	cos_angle = cos(angle);
	return (cos_angle);
}

float	ft_sin(float new_angle)
{
	static float	angle;
	static float	sin_angle;

	new_angle = (PI * new_angle) / 180;
	if (1 && new_angle == angle)
		return (sin_angle);
	angle = new_angle;
	sin_angle = sin(angle);
	return (sin_angle);
}

void	ft_rotateXYZ_point(t_point *p, t_point *rotated, t_setting *s)
{
	float	ax;
	float	ay;
	float	az;

	ax = s->angleX;
	ay = s->angleY;
	az = s->angleZ;
	rotated->x = p->x * (ft_cos(az) * ft_cos(ay) - ft_sin(az) * ft_sin(ax) * ft_sin(ay));
	rotated->x += p->y * (-ft_cos(ax) * ft_sin(az));
	rotated->x += p->z * (ft_cos(az) * ft_sin(ay) + ft_sin(az) * ft_sin(ax) * ft_cos(ay));
	rotated->y = p->x * (ft_sin(az) * ft_cos(ay) + ft_cos(az) * ft_sin(ax) * ft_sin(ay));
	rotated->y += p->y * (ft_cos(az) * ft_cos(ax));
	rotated->y += p->z * (ft_sin(az) * ft_sin(ay) - ft_cos(az) * ft_sin(ax) * ft_cos(ay));
	rotated->z = p->x * (-ft_cos(ax) * ft_sin(ay));
	rotated->z += p->y * ft_sin(ax);
	rotated->z += p->z * (ft_cos(ax) * ft_cos(ay));
	rotated->color = p->color;
}


