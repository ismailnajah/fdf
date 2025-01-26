/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_camera.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:42:09 by inajah            #+#    #+#             */
/*   Updated: 2025/01/26 10:56:15 by inajah           ###   ########.fr       */
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
	c->option[DOT_FACT] = 0;
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
	c.option[DOT_FACT] = 0;
	return (c);
}

t_camera	ft_camera_of_view(int view, t_camera *old)
{
	static t_camera	c;
	int				i;

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

void	ft_camera_update_zoom(t_camera *camera, t_mouse *mouse, int scale_step)
{
    float mousex = mouse->x - MENU_W;
    float mousey = mouse->y;

    float dx = mousex - camera->option[X_OFF];
    float dy = mousey - camera->option[Y_OFF];

    float new_scale = camera->option[SCALE] + scale_step;

    if (new_scale < MIN_ZOOM) new_scale = MIN_ZOOM;
    if (new_scale > MAX_ZOOM) new_scale = MAX_ZOOM;

    float scale_ratio = new_scale / camera->option[SCALE];
    camera->option[X_OFF] -= dx * (scale_ratio - 1);
    camera->option[Y_OFF] -= dy * (scale_ratio - 1);

    camera->option[SCALE] = new_scale;
}

void	ft_camera_update(t_camera *s, t_camera *e)
{
	int		i;
	float	*s_opt;
	float	*e_opt;

	s_opt = s->option;
	e_opt = e->option;
	i = 0;
	while (i < SCALE)
	{
		if (s_opt[i] != e_opt[i] && i <= ANGLE_Z)
			ft_camera_angle_update(&s_opt[i], s_opt[i] > e_opt[i]);
		else if (s_opt[i] != e_opt[i])
			ft_camera_offset_update(&s_opt[i], &e_opt[i]);
		i++;
	}
}
