/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:06:06 by inajah            #+#    #+#             */
/*   Updated: 2024/11/05 14:06:06 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long long	ft_abs(long long nb)
{
	if (nb < 0)
		return (-nb);
	return (nb);
}

char	ft_get_sign(long long d)
{
	if (d < 0)
		return ('-');
	return ('+');
}

int	ft_skip_digits(const char *fmt, size_t i)
{
	while (fmt[i] && ft_isdigit(fmt[i]))
		i++;
	return (i);
}

int	ft_padd_output(t_format *fmt, int str_size)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (i < fmt->width - str_size)
	{
		count += ft_putchar(fmt->padding_char);
		i++;
	}
	return (count);
}

int	ft_padd_nb_zeros(unsigned int nb, int precision, int base)
{
	int	nb_digits;
	int	count;

	count = 0;
	nb_digits = ft_count_digits_base(ft_abs(nb), base);
	while (nb_digits < precision)
	{
		count += ft_putchar('0');
		nb_digits++;
	}
	return (count);
}
