/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_label.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 14:08:34 by inajah            #+#    #+#             */
/*   Updated: 2024/11/30 12:08:07 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_label(t_vars *vars, int x, int y, char *text)
{
	mlx_string_put(vars->mlx, vars->win, x, y, C_WHITE, text);
}

void	ft_label_color_opt(t_vars *vars, char *buff)
{
	ft_label(vars, MENU_W * 0.2, MENU_H / 2 - 20, "Low  Point Color");
	ft_label(vars, MENU_W * 0.2, MENU_H / 2 + 40, "High Point Color");
	sprintf(buff, "0x");
	sprintf(buff + 2, "%.6X", vars->low_p->color);
	ft_label(vars, MENU_W * 0.7, MENU_H / 2 - 20, buff);
	sprintf(buff + 2, "%.6X", vars->high_p->color);
	ft_label(vars, MENU_W * 0.7, MENU_H / 2 + 40, buff);
}

void	ft_label_draw(t_vars *vars)
{
	static char	buff[14];
	t_camera	*c;
	int			i;
	int			label_y;

	c = vars->camera;
	i = 0;
	while (i < OPTION_COUNT)
	{
		label_y = c->field[i].y + c->field[i].h / 2 + 5;
		ft_label(vars, 20, label_y, vars->labels[i]);
		sprintf(buff, "%d", (int)c->option[i]);
		if (c->field[i].focused)
			ft_label(vars, c->field[i].x + 5, label_y, c->field[i].text);
		else
			ft_label(vars, c->field[i].x + 5, label_y, buff);
		i++;
	}
	ft_label(vars, MENU_W * 0.3, label_y + 50, vars->labels[i]);
	ft_label_color_opt(vars, buff);
}

char	**ft_labels_init(void)
{
	char	**labels;

	labels = (char **)malloc((OPTION_COUNT + 1) * sizeof(char *));
	if (!labels)
		return (NULL);
	labels[0] = "X-anlge [A/D]";
	labels[1] = "Y-angle [W/S]";
	labels[2] = "Z-angle [Q/E]";
	labels[3] = "X-offset [LEFT/RIGHT]";
	labels[4] = "Y-offset [UP/DOWN]";
	labels[5] = "Z-offset [-/+]";
	labels[6] = "Scale [Wheel]";
	labels[7] = "Doted lines factor";
	labels[8] = "< Press SPACE to reset view >";
	return (labels);
}
