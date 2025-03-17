/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:22:52 by inajah            #+#    #+#             */
/*   Updated: 2024/11/29 09:11:46 by inajah           ###   ########.fr       */
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

t_point	isometric_projection(t_point p)
{
	t_point	rot;
	float	ax;
	float	ay;
	float	az;

	ax = DEFAULT_ANGLE_X;
	ay = DEFAULT_ANGLE_Y;
	az = DEFAULT_ANGLE_Z;
	rot.x = p.x * (ft_cos(az) * ft_cos(ay) - ft_sin(az)
			* ft_sin(ax) * ft_sin(ay));
	rot.x += p.y * (-ft_cos(ax) * ft_sin(az));
	rot.x += p.z * (ft_cos(az) * ft_sin(ay) + ft_sin(az)
			* ft_sin(ax) * ft_cos(ay));
	rot.y = p.x * (ft_sin(az) * ft_cos(ay) + ft_cos(az)
			* ft_sin(ax) * ft_sin(ay));
	rot.y += p.y * (ft_cos(az) * ft_cos(ax));
	rot.y += p.z * (ft_sin(az) * ft_sin(ay) - ft_cos(az)
			* ft_sin(ax) * ft_cos(ay));
	rot.z = p.x * (-ft_cos(ax) * ft_sin(ay));
	rot.z += p.y * ft_sin(ax);
	rot.z += p.z * (ft_cos(ax) * ft_cos(ay));
	rot.color = p.color;
	return (rot);
}

void 	quaternion_rotation(t_point *p, t_point axis, double angle)
{
	angle = angle * (M_PI / 180);
	double half_theta = sin(angle / 2);
	double qx = axis.x * half_theta;
	double qy = axis.y * half_theta;
	double qz = axis.z * half_theta;
	double qw = cos(angle / 2);

	//p' = q * p * conj(q);
	double x = (1 - 2 * qy * qy - 2 * qz * qz) * p->x;
	x += (2 * qx * qy - 2 * qw * qz) * p->y;
	x += (2 * qx * qz + 2 * qw * qy) * p->z;

	double y = (2 * qx * qy + 2 * qw * qz) * p->x;
	y += (1 - 2 * qx * qx - 2 * qz * qz) * p->y;
	y += (2 * qy * qz - 2 * qw * qx) * p->z;

	double z = (2 * qx * qz - 2 * qw * qy) * p->x;
	z += (2 * qy * qz + 2 * qw * qx) * p->y;
	z += (1 - 2 * qx * qx - 2 * qy * qy) * p->z;

	p->x = x;
	p->y = y;
	p->z = z;
}

void	rotate_xyz_point(t_point *p, t_point *rot, t_camera *c)
{
	static bool first = true;
	static t_point x_axis;
	static t_point y_axis;
	static t_point z_axis;
	t_point	proj;

	if (first)
	{
		x_axis = isometric_projection((t_point){1, 0, 0, 0});
		y_axis = isometric_projection((t_point){0, 1, 0, 0});
		z_axis = isometric_projection((t_point){0, 0, 1, 0});
	}
	proj = isometric_projection(*p);
	
(void)c;
	//if (fabs(DEFAULT_ANGLE_X - c->option[ANGLE_X]) > EPSI)
		quaternion_rotation(&proj, x_axis, c->option[ANGLE_X]);
	//if (fabs(DEFAULT_ANGLE_Y - c->option[ANGLE_Y]) > EPSI)
		quaternion_rotation(&proj, y_axis, c->option[ANGLE_Y]);
	//if (fabs(DEFAULT_ANGLE_Z - c->option[ANGLE_Z]) > EPSI)
		quaternion_rotation(&proj, z_axis, c->option[ANGLE_Z]);
	rot->x = proj.x;
	rot->y = proj.y;
	rot->z = proj.z;
	rot->color = proj.color;
}