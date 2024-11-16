/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex_percent_spec.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:07:35 by inajah            #+#    #+#             */
/*   Updated: 2024/11/05 14:07:35 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	int	ft_padd_hex(t_format *fmt, int upper, int out_len)
{
	int	count;

	count = 0;
	if (!fmt->flags[DASH] && !fmt->flags[ZERO])
		count += ft_padd_output(fmt, out_len + (fmt->flags[HASH] * 2));
	if (fmt->flags[HASH])
	{
		if (upper)
			ft_putstr("0X");
		else
			ft_putstr("0x");
		count += 2;
	}
	if (!fmt->flags[DASH] && fmt->flags[ZERO])
		count += ft_padd_output(fmt, out_len + (fmt->flags[HASH] * 2));
	return (count);
}

int	ft_print_hex_spec(unsigned int x, int upper, t_format *fmt)
{
	int		out_len;
	int		count;

	count = 0;
	if (x == 0)
		return (ft_print_zero_value(fmt));
	out_len = ft_count_digits_base(x, 16);
	if (out_len < fmt->precision)
		out_len = fmt->precision;
	count += ft_padd_hex(fmt, upper, out_len);
	count += ft_padd_nb_zeros(x, fmt->precision, 16);
	if (upper)
		count += ft_print_decimal_to_base(x, "0123456789ABCDEF");
	else
		count += ft_print_decimal_to_base(x, "0123456789abcdef");
	if (fmt->flags[DASH])
		count += ft_padd_output(fmt, out_len + (fmt->flags[HASH] * 2));
	return (count);
}

int	ft_print_percent_spec(t_format *format)
{
	int	count;

	if (ft_detect_linux())
		return (ft_putchar('%'));
	count = 0;
	if (!format->flags[DASH])
		count += ft_padd_output(format, 1);
	count += ft_putchar('%');
	if (format->flags[DASH])
		count += ft_padd_output(format, 1);
	return (count);
}
