/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_camera.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:42:09 by inajah            #+#    #+#             */
/*   Updated: 2024/11/24 21:46:40 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	*ft_camera_free(t_camera *c)
{
	free(c->field);
	free(c);
	return (NULL);
}

t_camera	*ft_camera_init(void)
{
	t_camera	*c;

	c = (t_camera *)malloc(sizeof(t_camera));
	if (!c)
		return (NULL);
	c->option[ANGLE_X] = DEFAULT_ANGLE_X;
	c->option[ANGLE_Y] = DEFAULT_ANGLE_Y;
	c->option[ANGLE_Z] = DEFAULT_ANGLE_Z;
	c->option[SCALE] = DEFAULT_SCALE;
	c->option[X_OFF] = DEFAULT_X_OFF;
	c->option[Y_OFF] = DEFAULT_Y_OFF;
	c->option[Z_OFF] = DEFAULT_Z_OFF;
	c->field = ft_text_field_init(c);
	if (!c->field)
		return (ft_camera_free(c));
	return (c);
}

t_camera	ft_camera_default(void)
{
	static t_camera	c;

	c.option[ANGLE_X] = DEFAULT_ANGLE_X;
	c.option[ANGLE_Y] = DEFAULT_ANGLE_Y;
	c.option[ANGLE_Z] = DEFAULT_ANGLE_Z;
	c.option[SCALE] = DEFAULT_SCALE;
	c.option[X_OFF] = DEFAULT_X_OFF;
	c.option[Y_OFF] = DEFAULT_Y_OFF;
	c.option[Z_OFF] = DEFAULT_Z_OFF;
	return (c);
}

t_camera	ft_camera_of_view(int view, t_camera *old)
{
	static t_camera	c;
	int	i;

	i = 0;
	while (old && i < OPTION_COUNT)
	{
		c.option[i] = old->option[i];
		i++;
	}
	c.option[ANGLE_X] = 0.0f;
	c.option[ANGLE_Y] = 0.0f;
	c.option[ANGLE_Z] = 0.0f;
	if (view == TOP_VIEW)
		return (c);
	if (view == SIDE_VIEW)
		c.option[ANGLE_X] = 90.0f;
	if (view == FRONT_VIEW)
	{
		c.option[ANGLE_Y] = 90.0f;
		c.option[ANGLE_Z] = -90.0f;
	}
	return (c);
}

void	ft_camera_animate(t_camera *s, t_camera *e)
{
	int i;

	i = 0;
	while (i < OPTION_COUNT - 2) // ignore scale and z_offset
	{
		if (s->option[i] != e->option[i] && i <= ANGLE_Z)
			ft_angle_change(&s->option[i], s->option[i] > e->option[i]);
		else if (s->option[i] != e->option[i])
			s->option[i] += (1 - 2 * (s->option[i] > e->option[i])) * OFFSET_STEP;
		i++;
	}
}
