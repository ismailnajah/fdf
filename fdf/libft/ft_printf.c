/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:07:57 by inajah            #+#    #+#             */
/*   Updated: 2024/11/05 14:07:57 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	resolve_format(t_format *fmt)
{
	if (fmt->flags[DASH] || fmt->flags[DOT])
	{
		fmt->flags[ZERO] = 0;
		fmt->padding_char = ' ';
	}
	if (fmt->flags[PLUS])
		fmt->flags[SPACE] = 0;
	if (fmt->specifier == UNSIGNED_DECIMAL)
		fmt->flags[PLUS] = 0;
}

static int	print_arg_using_format(va_list ap, t_format *fmt)
{
	t_specifier		s;

	s = fmt->specifier;
	if (s == CHAR)
		return (ft_print_char_spec(va_arg(ap, int), fmt));
	if (s == STRING)
		return (ft_print_str_spec(va_arg(ap, char *), fmt));
	if (s == ADDRESS)
		return (ft_print_addr_spec(va_arg(ap, void *), fmt));
	if (s == SIGNED_DECIMAL)
		return (ft_print_dec_spec(va_arg(ap, int), fmt));
	if (s == UNSIGNED_DECIMAL)
		return (ft_print_udec_spec(va_arg(ap, unsigned int), fmt));
	if (s == LOWER_HEX)
		return (ft_print_hex_spec(va_arg(ap, unsigned int), 0, fmt));
	if (s == UPPER_HEX)
		return (ft_print_hex_spec(va_arg(ap, unsigned int), 1, fmt));
	if (s == PERCENT_SIGN)
		return (ft_print_percent_spec(fmt));
	return (0);
}

static int	print_next_arg(const char *str, int *i, va_list ap, t_format *fmt)
{
	int	end;
	int	count;

	count = 0;
	end = ft_parse_format(str, *i + 1, fmt);
	if (end)
	{
		resolve_format(fmt);
		count = print_arg_using_format(ap, fmt);
		*i = end + 1;
	}
	return (count);
}

static int	print_fmt_str(const char *fmt_str, va_list ap, t_format *fmt)
{
	int	count;
	int	i;
	int	ret;

	count = 0;
	i = 0;
	while (fmt_str[i])
	{
		if (fmt_str[i] == '%')
		{
			ft_fmt_reset(fmt);
			ret = print_next_arg(fmt_str, &i, ap, fmt);
			if (!ret && fmt->specifier == INVALID_SPECIFIER)
			{
				if (ft_detect_linux())
					count += ft_putchar('%');
				i++;
			}
			count += ret;
			continue ;
		}
		count += ft_putchar(fmt_str[i]);
		i++;
	}
	return (count);
}

int	ft_printf(const char *fmt_str, ...)
{
	va_list		ap;
	int			count;
	t_format	*fmt;

	if (!fmt_str && ft_detect_linux())
		return (-1);
	va_start(ap, fmt_str);
	fmt = ft_fmt_init();
	if (!fmt)
		return (-1);
	count = print_fmt_str(fmt_str, ap, fmt);
	ft_fmt_clear(&fmt);
	va_end(ap);
	if (ft_error(ERROR_GET))
		count = -1;
	ft_error(ERROR_RESET);
	return (count);
}
