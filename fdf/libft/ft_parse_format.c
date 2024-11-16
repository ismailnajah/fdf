/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:07:48 by inajah            #+#    #+#             */
/*   Updated: 2024/11/05 14:07:48 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_flag	is_flag(char c)
{
	if (c == '#')
		return (HASH);
	if (c == ' ')
		return (SPACE);
	if (c == '.')
		return (DOT);
	if (c == '-')
		return (DASH);
	if (c == '+')
		return (PLUS);
	if (c == '0')
		return (ZERO);
	return (INVALID_FLAG);
}

static t_specifier	is_specifier(char c)
{
	if (c == 'c')
		return (CHAR);
	if (c == 's')
		return (STRING);
	if (c == 'p')
		return (ADDRESS);
	if (c == 'd' || c == 'i')
		return (SIGNED_DECIMAL);
	if (c == 'u')
		return (UNSIGNED_DECIMAL);
	if (c == 'x')
		return (LOWER_HEX);
	if (c == 'X')
		return (UPPER_HEX);
	if (c == '%')
		return (PERCENT_SIGN);
	return (INVALID_SPECIFIER);
}

static int	ft_parse_validate(const char *fmt_str, size_t index, t_format *fmt)
{
	t_specifier	s;

	s = is_specifier(fmt_str[index]);
	if (s == INVALID_SPECIFIER)
		return (0);
	else
		fmt->specifier = s;
	return (index);
}

static int	ft_parse_digits(const char *fmt_str, size_t index, t_format *fmt)
{
	if (fmt->flags[DOT])
		fmt->precision = ft_atoi(fmt_str + index);
	else
		fmt->width = ft_atoi(fmt_str + index);
	index = ft_skip_digits(fmt_str, index);
	if (is_flag(fmt_str[index]) == DOT)
	{
		fmt->flags[DOT] = 1;
		fmt->precision = ft_atoi(fmt_str + index + 1);
		index = ft_skip_digits(fmt_str, index + 1);
	}
	return (ft_parse_validate(fmt_str, index, fmt));
}

int	ft_parse_format(const char *fmt_str, size_t start, t_format *fmt)
{
	t_flag	flag_kind;
	size_t	i;

	i = start;
	while (fmt_str[i])
	{
		flag_kind = is_flag(fmt_str[i]);
		if (!flag_kind && !ft_isdigit(fmt_str[i]))
			return (ft_parse_validate(fmt_str, i, fmt));
		else if (flag_kind == ZERO)
		{
			fmt->flags[ZERO] = 1;
			fmt->padding_char = '0';
		}
		else if (ft_isdigit(fmt_str[i]))
			return (ft_parse_digits(fmt_str, i, fmt));
		fmt->flags[flag_kind] = 1;
		i++;
	}
	return (0);
}
