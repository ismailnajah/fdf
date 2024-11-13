/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:54:31 by inajah            #+#    #+#             */
/*   Updated: 2024/11/05 13:54:31 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar(char c)
{
	int	ret;

	ret = 0;
	if (!ft_error(ERROR_GET))
		ret = write(STDOUT, &c, 1);
	if (ret == -1)
		ft_error(ERROR_HAPPENED);
	return (1);
}
