/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addr_spec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:05:51 by inajah            #+#    #+#             */
/*   Updated: 2024/11/05 14:05:51 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_addr_spec(void *addr, t_format *fmt)
{
	size_t	nb;
	size_t	out_len;
	int		count;
	int		is_linux;

	is_linux = ft_detect_linux();
	count = 0;
	nb = (size_t) addr;
	out_len = ft_count_digits_base(nb, 16);
	out_len += 2 * !is_linux + is_linux * (2 + 2 * (addr == NULL));
	if (!fmt->flags[DASH])
		count += ft_padd_output(fmt, out_len);
	if ((is_linux && addr) || !is_linux)
		count += ft_putstr("0x");
	if (!addr && is_linux)
		count += ft_putstr("(nil)");
	else
		count += ft_print_decimal_to_base(nb, "0123456789abcdef");
	if (fmt->flags[DASH])
		count += ft_padd_output(fmt, out_len);
	return (count);
}
