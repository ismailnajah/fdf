/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:07:25 by inajah            #+#    #+#             */
/*   Updated: 2024/11/05 14:07:25 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_format	*ft_fmt_init(void)
{
	t_format	*fmt;

	fmt = (t_format *)ft_calloc(1, sizeof(t_format));
	if (!fmt)
		return (NULL);
	fmt->flags = (t_flag *)ft_calloc(FLAG_COUNT, sizeof(t_flag));
	if (!fmt->flags)
	{
		free(fmt);
		return (NULL);
	}
	fmt->width = 0;
	fmt->precision = 0;
	fmt->padding_char = ' ';
	fmt->specifier = INVALID_SPECIFIER;
	return (fmt);
}

void	ft_fmt_clear(t_format **fmt)
{
	free((*fmt)->flags);
	(*fmt)->flags = NULL;
	free(*fmt);
	*fmt = NULL;
}

void	ft_fmt_reset(t_format *fmt)
{
	size_t	i;

	i = 0;
	while (i < FLAG_COUNT)
		fmt->flags[i++] = 0;
	fmt->width = 0;
	fmt->precision = 0;
	fmt->padding_char = ' ';
	fmt->specifier = INVALID_SPECIFIER;
}
