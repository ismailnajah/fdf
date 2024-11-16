/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_d_i_u_spec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:07:03 by inajah            #+#    #+#             */
/*   Updated: 2024/11/05 14:07:03 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_zero_value(t_format *fmt)
{
	int	count;
	int	out_len;

	count = 0;
	if (!fmt->flags[DOT])
		fmt->precision += 1;
	out_len = fmt->flags[PLUS] + fmt->flags[SPACE];
	out_len += fmt->precision;
	if (fmt->flags[SPACE])
		count += ft_putchar(' ');
	if (fmt->flags[PLUS] && fmt->padding_char == '0')
		count += ft_putchar('+');
	if (!fmt->flags[DASH])
		count += ft_padd_output(fmt, out_len);
	if (fmt->flags[PLUS] && fmt->padding_char != '0')
		count += ft_putchar('+');
	count += ft_padd_nb_zeros(0, fmt->precision + 1, 10);
	if (fmt->flags[DASH])
		count += ft_padd_output(fmt, out_len);
	return (count);
}

static int	resolve_nb_padding(unsigned int d, int size, t_format *fmt, char s)
{
	int	padd_len;
	int	count;

	count = 0;
	padd_len = size + (fmt->flags[PLUS] || s == '-');
	if ((fmt->flags[PLUS] || s == '-') && fmt->flags[ZERO])
		count += ft_putchar(s);
	if (!fmt->flags[DASH])
		count += ft_padd_output(fmt, padd_len);
	if ((fmt->flags[PLUS] || s == '-') && !fmt->flags[ZERO])
		count += ft_putchar(s);
	count += ft_padd_nb_zeros(d, fmt->precision, 10);
	return (count);
}

static int	print_number_specifier(unsigned long d, char s, t_format *fmt)
{
	int		out_len;
	int		count;

	if (d == 0)
		return (ft_print_zero_value(fmt));
	count = 0;
	out_len = ft_count_digits_base(d, 10);
	if (out_len < fmt->precision)
		out_len = fmt->precision;
	if (fmt->flags[SPACE] && s == '+')
	{
		out_len += 1;
		count += ft_putchar(' ');
	}
	count += resolve_nb_padding(ft_abs(d), out_len, fmt, s);
	count += ft_print_decimal_to_base(d, "0123456789");
	if (fmt->flags[DASH])
		count += ft_padd_output(fmt, out_len + (fmt->flags[PLUS] || s == '-'));
	return (count);
}

int	ft_print_dec_spec(int d, t_format *fmt)
{
	char	sign;

	sign = ft_get_sign(d);
	return (print_number_specifier(ft_abs(d), sign, fmt));
}

int	ft_print_udec_spec(unsigned int u, t_format *fmt)
{
	return (print_number_specifier(u, '+', fmt));
}
