/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_label.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 14:08:34 by inajah            #+#    #+#             */
/*   Updated: 2024/11/27 14:09:46 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_label(t_vars *vars, int x, int y, char *text)
{
	mlx_string_put(vars->mlx, vars->win, x, y, C_WHITE, text);
}

char	**ft_labels_init(void)
{
	char	**labels;

	labels = (char **)malloc(OPTION_COUNT * sizeof(char *));
	if (!labels)
		return (NULL);
	labels[0] = "X-anlge [A/D]";
	labels[1] = "Y-angle [W/S]";
	labels[2] = "Z-angle [Q/E]";
	labels[3] = "X-offset [LEFT/RIGHT]";
	labels[4] = "Y-offset [UP/DOWN]";
	labels[5] = "Z-offset [-/+]";
	labels[6] = "Scale [Wheel]";
	return (labels);
}
