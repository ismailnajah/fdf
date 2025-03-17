/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:01:47 by inajah            #+#    #+#             */
/*   Updated: 2025/01/26 10:10:19 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	*image_free(void *mlx, t_image *img)
{
	if (!img)
		return (NULL);
	mlx_destroy_image(mlx, img->data);
	free(img);
	return (NULL);
}

t_image	*image_init(void *mlx, int width, int height)
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
		return (image_free(mlx, img));
	img->w = width;
	img->h = height;
	img->focused = false;
	return (img);
}

void	image_clear(t_image *img, unsigned int color)
{
	int	i;
	int	j;

	j = 0;
	while (j < img->h)
	{
		i = 0;
		while (i < img->w)
		{
			draw_pixel(img, i, j, color);
			i++;
		}
		j++;
	}
}

void	*layout_free(void *mlx, t_layout *layout)
{
	if (!layout)
		return (NULL);
	image_free(mlx, layout->main);
	image_free(mlx, layout->cube_view);
	image_free(mlx, layout->menu);
	free(layout);
	return (NULL);
}

t_layout	*layout_init(void *mlx)
{
	t_layout	*layout;

	layout = (t_layout *)malloc(sizeof(t_layout));
	if (!layout)
		return (NULL);
	layout->main = image_init(mlx, MAIN_W, MAIN_H);
	if (!layout->main)
		return (layout_free(mlx, layout));
	layout->cube_view = image_init(mlx, CUBE_W, CUBE_H);
	if (!layout->cube_view)
		return (layout_free(mlx, layout));
	layout->menu = image_init(mlx, MENU_W, MENU_H);
	if (!layout->menu)
		return (layout_free(mlx, layout));
	image_clear(layout->menu, C_GREY);
	return (layout);
}

void	layout_set_image_focused(t_layout *layout, int x, int y)
{
	if (x < layout->menu->w)
		layout->menu->focused = true;
	else if (x > WIN_H - layout->cube_view->w && y < layout->cube_view->h)
		layout->cube_view->focused = true;
	else
		layout->main->focused = true;
}

void	layout_reset_image_focused(t_layout *layout)
{
	layout->menu->focused = false;
	layout->cube_view->focused = false;
	layout->main->focused = false;
}
