/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_camera_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 09:11:15 by inajah            #+#    #+#             */
/*   Updated: 2024/11/29 15:34:40 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_camera_angle_update(float *angle, int direction)
{
	direction = (1 - 2 * direction);
	*angle = ft_fmod(*angle + direction * ANGLE_STEP, 360.0f);
}

void	ft_camera_offset_update(float *s, float *e)
{
	if (*s < *e)
	{
		*s += OFFSET_STEP;
		if (*s > *e)
			*s = *e;
	}
	else if (*s > *e)
	{
		*s -= OFFSET_STEP;
		if (*s < *e)
			*s = *e;
	}
}
