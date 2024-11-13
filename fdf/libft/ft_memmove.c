/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:54:56 by inajah            #+#    #+#             */
/*   Updated: 2024/11/05 13:54:56 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*from;
	unsigned char	*to;

	from = (unsigned char *)src;
	to = (unsigned char *)dest;
	if (from == to || n == 0)
		return (dest);
	if (from < to)
	{
		while (n > 0)
		{
			to[n - 1] = from[n - 1];
			n--;
		}
		return (dest);
	}
	return (ft_memcpy(dest, src, n));
}
