/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 09:31:58 by inajah            #+#    #+#             */
/*   Updated: 2025/01/26 09:50:03 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_mouse *mouse_init(void)
{
	t_mouse	*mouse;

	mouse = malloc(sizeof(t_mouse));
	if (mouse == NULL)
		return (NULL);
	mouse->x = 0;
	mouse->y = 0;
	mouse->lepressed = false;
	mouse->right_pressed = false;
	return (mouse);
}

void	mouse_update_position(t_vars *vars, int x, int y)
{
	vars->mouse->x = x;
	vars->mouse->y = y;
}
