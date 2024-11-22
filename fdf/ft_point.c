/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_point.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:55:54 by inajah            #+#    #+#             */
/*   Updated: 2024/11/22 17:33:15 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_point_swap(t_point *a, t_point *b)
{
	float			tmp;
	unsigned int	c;

	tmp = b->x;
	b->x = a->x;
	a->x = tmp;
	tmp = b->y;
	b->y = a->y;
	a->y = tmp;
	tmp = b->z;
	b->z = a->z;
	a->z = tmp;
	c = b->color;
	b->color = a->color;
	a->color = c;
}

int	ft_point_sort(t_point *a, t_point *b)
{
	if (fabs(a->x - b->x) < fabs(a->y - b->y))
	{
		if (a->y > b->y)
			ft_point_swap(a, b);
		return (1);
	}
	else if (a->x > b->x)
		ft_point_swap(a, b);
	return (0);
}

void	ft_point_scale(t_point *a, t_point *p, t_setting *s)
{
	a->x = p->x * s->scale + s->x_off;
	a->y = p->y * s->scale + s->y_off;
	a->color = p->color;
}
