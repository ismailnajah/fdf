/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dec_to_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:07:13 by inajah            #+#    #+#             */
/*   Updated: 2024/11/05 14:07:13 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_count_digits_base(unsigned long nb, size_t base)
{
	int	count;

	count = 1;
	while (nb >= base)
	{
		count++;
		nb /= base;
	}
	return (count);
}

int	ft_print_decimal_to_base(unsigned long nb, char *base_symb)
{
	char	out[50];
	size_t	out_len;
	size_t	base;
	size_t	i;

	base = ft_strlen(base_symb);
	out_len = ft_count_digits_base(nb, base);
	out[out_len] = 0;
	i = out_len - 1;
	while (nb >= base)
	{
		out[i] = base_symb[nb % base];
		nb /= base;
		i--;
	}
	out[i] = base_symb[nb % base];
	return (ft_putstr(out));
}
