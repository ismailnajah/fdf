/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:22:52 by inajah            #+#    #+#             */
/*   Updated: 2024/11/21 10:12:51 by inajah           ###   ########.fr       */
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

void	*ft_matrix_free(t_matrix *mat)
{
	if (mat)
		free(mat->values);
	free(mat);
	return (NULL);
}

t_matrix	*ft_matrix_init(int w, int h)
{
	t_matrix	*mat;

	mat = (t_matrix*)malloc(sizeof(t_matrix));
	if (!mat)
		return (NULL);
	mat->w = w;
	mat->h = h;
	mat->values = (float*)malloc(w * h * sizeof(float));
	if (!mat->values)
	{
		free(mat);
		return (NULL);
	}
	return (mat);
}

void	ft_matrix_point_mul(t_matrix *mat, t_point *p, t_point *out)
{
	float	*m;
	int		w;
	
	if (mat->w != 3)
	{
		ft_printf("[ ERROR ] matrix multiplication: matrix cols (%d) != point rows (3)\n", mat->w);
		return ;
	}
	m = mat->values;
	w = mat->w;
	out->x = m[w * 0 + 0] * p->x + m[w * 0 + 1] * p->y + m[w * 0 + 2] * p->z;
	out->y = m[w * 1 + 0] * p->x + m[w * 1 + 1] * p->y + m[w * 1 + 2] * p->z;
	out->z = m[w * 2 + 0] * p->x + m[w * 2 + 1] * p->y + m[w * 2 + 2] * p->z;
	out->color = p->color;
}

void	ft_matrix_rotateX(t_matrix *mat, float angle)
{
	float	*m;
	int		w;

	w = mat->w;
	m = mat->values;
	//first row
	m[w * 0 + 0] = 1;
	m[w * 0 + 1] = 0;
	m[w * 0 + 2] = 0;
	//second row	
	m[w * 1 + 0] = 0;
	m[w * 1 + 1] = ft_cos(angle);
	m[w * 1 + 2] = -ft_sin(angle);
	//third row	
	m[w * 2 + 0] = 0;
	m[w * 2 + 1] = ft_sin(angle);
	m[w * 2 + 2] = ft_cos(angle);
}

void	ft_matrix_rotateY(t_matrix *mat, float angle)
{
	float	*m;
	int		w;

	w = mat->w;
	m = mat->values;
	//first row
	m[w * 0 + 0] = ft_cos(angle);
	m[w * 0 + 1] = 0;
	m[w * 0 + 2] = ft_sin(angle);
	//second row	
	m[w * 1 + 0] = 0;
	m[w * 1 + 1] = 1;
	m[w * 1 + 2] = 0;
	//third row	
	m[w * 2 + 0] = -ft_sin(angle);
	m[w * 2 + 1] = 0;
	m[w * 2 + 2] = ft_cos(angle);
}

void	ft_matrix_rotateZ(t_matrix *mat, float angle)
{
	float	*m;
	int		w;

	w = mat->w;
	m = mat->values;
	//first row
	m[w * 0 + 0] = ft_cos(angle);
	m[w * 0 + 1] = -ft_sin(angle);
	m[w * 0 + 2] = 0;
	//second row	
	m[w * 1 + 0] = ft_sin(angle);
	m[w * 1 + 1] = ft_cos(angle);
	m[w * 1 + 2] = 0;
	//third row	
	m[w * 2 + 0] = 0;
	m[w * 2 + 1] = 0;
	m[w * 2 + 2] = 1;
}


void	ft_project_point_v2(t_point *p, t_point *projected, t_setting *s)
{
	float	ax;
	float	ay;
	float	az;

	ax = s->angleX;
	ay = s->angleY;
	az = s->angleZ;
	projected->x = p->x * (ft_cos(az) * ft_cos(ay) - ft_sin(az) * ft_sin(ax) * ft_sin(ay));
	projected->x += p->y * (-ft_cos(ax) * ft_sin(az));
	projected->x += p->z * (ft_cos(az) * ft_sin(ay) + ft_sin(az) * ft_sin(ax) * ft_cos(ay));
	projected->y = p->x * (ft_sin(az) * ft_cos(ay) + ft_cos(az) * ft_sin(ax) * ft_sin(ay));
	projected->y += p->y * (ft_cos(az) * ft_cos(ax));
	projected->y += p->z * (ft_sin(az) * ft_sin(ay) - ft_cos(az) * ft_sin(ax) * ft_cos(ay));
	projected->z = p->x * (-ft_cos(ax) * ft_sin(ay));
	projected->z += p->y * ft_sin(ax);
	projected->z += p->z * (ft_cos(ax) * ft_cos(ay));
	projected->color = p->color;
}


