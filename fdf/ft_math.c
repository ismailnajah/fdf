/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:22:52 by inajah            #+#    #+#             */
/*   Updated: 2024/11/24 21:00:31 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	ft_cos(float new_angle)
{
	static int		flag;
	static float	angle;
	static float	cos_angle;

	new_angle = (PI * new_angle) / 180;
	if (flag == 0)
	{
		flag = 1;
		cos_angle = 1;
	}
	if (new_angle == angle)
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
	if (new_angle == angle)
		return (sin_angle);
	angle = new_angle;
	sin_angle = sin(angle);
	return (sin_angle);
}

void	ft_rotate_xyz_point(t_point *p, t_point *rot, t_camera *c)
{
	float	ax;
	float	ay;
	float	az;

	ax = c->option[ANGLE_X];
	ay = c->option[ANGLE_Y];
	az = c->option[ANGLE_Z];
	rot->x = p->x * (ft_cos(az) * ft_cos(ay) - ft_sin(az)
			* ft_sin(ax) * ft_sin(ay));
	rot->x += p->y * (-ft_cos(ax) * ft_sin(az));
	rot->x += p->z * (ft_cos(az) * ft_sin(ay) + ft_sin(az)
			* ft_sin(ax) * ft_cos(ay));
	rot->y = p->x * (ft_sin(az) * ft_cos(ay) + ft_cos(az)
			* ft_sin(ax) * ft_sin(ay));
	rot->y += p->y * (ft_cos(az) * ft_cos(ax));
	rot->y += p->z * (ft_sin(az) * ft_sin(ay) - ft_cos(az)
			* ft_sin(ax) * ft_cos(ay));
	rot->z = p->x * (-ft_cos(ax) * ft_sin(ay));
	rot->z += p->y * ft_sin(ax);
	rot->z += p->z * (ft_cos(ax) * ft_cos(ay));
	rot->color = p->color;
}

float	ft_fmod(float value, float div)
{
	int		sign;
	float	abs_value;

	abs_value = fabs(value);
	sign = 1 - 2 * (value < 0.0f);
	if (abs_value >= div)
		return ((abs_value - div) * sign);
	return (value);
}

void	ft_angle_change(float *angle, int direction)
{
	direction = (1 - 2 * direction);
	*angle = ft_fmod(*angle + direction * ANGLE_STEP, 360.0f);
}
