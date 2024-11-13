/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:01:19 by inajah            #+#    #+#             */
/*   Updated: 2024/11/05 14:01:19 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_nb_digits(long long nb)
{
	size_t	size;

	if (nb == 0)
		return (1);
	size = 0;
	while (nb > 0)
	{
		size++;
		nb = nb / 10;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char		*buffer;
	size_t		i;
	long long	nb;
	size_t		buffer_size;
	size_t		sign;

	sign = (n < 0);
	nb = n * (1 - 2 * sign);
	buffer_size = get_nb_digits(nb) + sign;
	buffer = (char *)malloc((buffer_size + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	if (sign)
		buffer[0] = '-';
	i = buffer_size - 1;
	while (nb >= 10)
	{
		buffer[i--] = '0' + (nb % 10);
		nb /= 10;
	}
	buffer[i] = '0' + nb;
	buffer[buffer_size] = '\0';
	return (buffer);
}
