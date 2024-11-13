/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:51:21 by inajah            #+#    #+#             */
/*   Updated: 2024/11/05 13:51:21 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	size_t	set_len;

	if (!s1 || !set)
		return (NULL);
	set_len = ft_strlen(set);
	start = 0;
	while (s1[start] && ft_memchr(set, s1[start], set_len))
		start++;
	if (!s1[start])
		return (ft_calloc(1, sizeof(char)));
	end = ft_strlen(s1) - 1;
	while (end >= 0 && ft_memchr(set, s1[end], set_len))
		end--;
	return (ft_substr(s1, start, end - start + 1));
}
