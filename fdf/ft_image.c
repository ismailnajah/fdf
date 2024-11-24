/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_image.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:01:47 by inajah            #+#    #+#             */
/*   Updated: 2024/11/24 23:00:50 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	*ft_image_free(void *mlx, t_image *img)
{
	if (!img)
		return (NULL);
	mlx_destroy_image(mlx, img->data);
	free(img);
	return (NULL);
}

t_image	*ft_image_init(void *mlx, int width, int height)
{
	t_image	*img;

	img = (t_image *)malloc(sizeof(t_image));
	if (!img)
		return (NULL);
	img->data = mlx_new_image(mlx, width, height);
	if (!img->data)
		return (ft_abort(img));
	img->addr = mlx_get_data_addr(img->data, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	if (!img->addr)
		return (ft_image_free(mlx, img));
	img->w = width;
	img->h = height;
	return (img);
}

void	ft_image_clear(t_image *img, unsigned int color)
{
	int	i;
	int	j;

	j = 0;
	while (j < img->h)
	{
		i = 0;
		while (i < img->w)
		{
			ft_draw_pixel(img, i, j, color);
			i++;
		}
		j++;
	}
}

void	*ft_layout_free(void *mlx, t_layout *layout)
{
	if (!layout)
		return (NULL);
	ft_image_free(mlx, layout->main);
	ft_image_free(mlx, layout->cube_view);
	ft_image_free(mlx, layout->menu);
	free(layout);
	return (NULL);
}

t_layout	*ft_layout_init(void *mlx)
{
	t_layout	*layout;

	layout = (t_layout *)malloc(sizeof(t_layout));
	if (!layout)
		return (NULL);
	layout->main = ft_image_init(mlx, MAIN_W, MAIN_H);
	if (!layout->main)
		return (ft_layout_free(mlx, layout));
	layout->cube_view = ft_image_init(mlx, CUBE_W, CUBE_H);
	if (!layout->cube_view)
		return (ft_layout_free(mlx, layout));	
	layout->menu = ft_image_init(mlx, MENU_W, MENU_H);
	if (!layout->menu)
		return (ft_layout_free(mlx, layout));
	ft_image_clear(layout->menu, C_GREY);
	return (layout);
}
