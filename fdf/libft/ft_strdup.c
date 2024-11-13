/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:53:10 by inajah            #+#    #+#             */
/*   Updated: 2024/11/05 13:53:10 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*copy;
	int		n;

	n = ft_strlen(str);
	copy = (char *)malloc((n + 1) * sizeof(char));
	if (!copy)
		return (NULL);
	ft_memcpy(copy, str, n);
	copy[n] = '\0';
	return (copy);
}
