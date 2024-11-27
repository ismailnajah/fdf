/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_point.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:55:54 by inajah            #+#    #+#             */
/*   Updated: 2024/11/27 10:37:56 by inajah           ###   ########.fr       */
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

void	ft_point_scale(t_point *a, t_point *p, t_camera *c)
{
	a->x = p->x * c->option[SCALE] + c->option[X_OFF];
	a->y = p->y * c->option[SCALE] + c->option[Y_OFF];
	a->color = p->color;
}

void	ft_point_copy(t_point	*dst, t_point *src)
{
	dst->x = src->x;
	dst->y = src->y;
	dst->z = src->z;
	dst->color = src->color;
}

t_point *ft_point_init(float x, float y, float z, unsigned int color)
{
	t_point	*p;

	p = (t_point *)malloc(sizeof(t_point));
	if (!p)
		return (NULL);
	p->x = x;
	p->y = y;
	p->z = z;
	p->color = color;
	return (p);
}
