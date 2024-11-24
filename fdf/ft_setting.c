/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:42:09 by inajah            #+#    #+#             */
/*   Updated: 2024/11/24 16:31:28 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_setting	*ft_setting_init(void)
{
	t_setting	*s;

	s = (t_setting *)malloc(sizeof(t_setting));
	if (!s)
		return (NULL);
	s->angleX = DEFAULT_ANGLE_X;
	s->angleY = DEFAULT_ANGLE_Y;
	s->angleZ = DEFAULT_ANGLE_Z;
	s->scale = DEFAULT_SCALE;
	s->x_off = DEFAULT_X_OFF;
	s->y_off = DEFAULT_Y_OFF;
	s->z_off = DEFAULT_Z_OFF;
	ft_text_field_init(s);
	return (s);
}

t_setting	ft_setting_default(void)
{
	t_setting	s;

	s.angleX = DEFAULT_ANGLE_X;
	s.angleY = DEFAULT_ANGLE_Y;
	s.angleZ = DEFAULT_ANGLE_Z;
	s.scale = DEFAULT_SCALE;
	s.x_off = DEFAULT_X_OFF;
	s.y_off = DEFAULT_Y_OFF;
	s.z_off = DEFAULT_Z_OFF;
	return (s);
}

t_setting	ft_setting_of_view(int view, t_setting *old_s)
{
	static t_setting	s;

	if (old_s)
	{
		s.scale = old_s->scale;
		s.x_off = old_s->x_off;
		s.y_off = old_s->y_off;
		s.z_off = old_s->z_off;
	}
	s.angleX = 0.0f;
	s.angleY = 0.0f;
	s.angleZ = 0.0f;
	if (view == TOP_VIEW)
		return (s);
	if (view == SIDE_VIEW)
		s.angleX = 90.0f;
	if (view == FRONT_VIEW)
	{
		s.angleY = 90.0f;
		s.angleZ = -90.0f;
	}
	return (s);
}

void	ft_setting_animate(t_setting *s, t_setting *e)
{
	if (s->angleX != e->angleX)
		ft_angle_change(&s->angleX, s->angleX > e->angleX);
	if (s->angleY != e->angleY)
		ft_angle_change(&s->angleY, s->angleY > e->angleY);
	if (s->angleZ != e->angleZ)
		ft_angle_change(&s->angleZ, s->angleZ > e->angleZ);
	if (s->x_off != e->x_off)
		s->x_off += (1 - 2 * (s->x_off > e->x_off)) * OFFSET_STEP;
	if (s->y_off != e->y_off)
		s->y_off += (1 - 2 * (s->y_off > e->y_off)) * OFFSET_STEP;
}

void	print_setting(t_setting *s)
{
	printf("[ angleX: %.2f | ", s->angleX);
	printf("angleY: %.2f | ", s->angleY);
	printf("angleZ: %.2f | ", s->angleZ);
	printf("scale: %d | ", s->scale);
	printf("x_off: %d | ", s->x_off);
	printf("y_off: %d | ", s->y_off);
	printf("z_off: %.2f ]\n", s->z_off);
}
