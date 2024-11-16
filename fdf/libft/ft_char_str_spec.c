/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_str_spec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:06:48 by inajah            #+#    #+#             */
/*   Updated: 2024/11/05 14:06:48 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_char_spec(char c, t_format *fmt)
{
	int		count;

	count = 0;
	if (!fmt->flags[DASH])
		count += ft_padd_output(fmt, 1);
	count += ft_putchar(c);
	if (fmt->flags[DASH])
		count += ft_padd_output(fmt, 1);
	return (count);
}

int	ft_print_str_spec(char *str, t_format *fmt)
{
	int	count;
	int	i;
	int	out_len;

	if (!str)
	{
		str = "(null)";
		if (ft_detect_linux() && fmt->flags[DOT] && fmt->precision < 6)
			str = "";
	}
	count = 0;
	i = 0;
	out_len = ft_strlen(str);
	if (fmt->flags[DOT] && out_len > fmt->precision)
		out_len = fmt->precision;
	if (!fmt->flags[DASH])
		count += ft_padd_output(fmt, out_len);
	while (i < out_len)
		count += ft_putchar(str[i++]);
	if (fmt->flags[DASH])
		count += ft_padd_output(fmt, out_len);
	return (count);
}
