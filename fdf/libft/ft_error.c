/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:01:13 by inajah            #+#    #+#             */
/*   Updated: 2024/11/13 14:47:21 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifdef __linux__

int	ft_detect_linux(void)
{
	return (1);
}

#else

int	ft_detect_linux(void)
{
	return (0);
}

#endif

int	ft_error(int error_flag)
{
	static int	error;

	if (error_flag == ERROR_HAPPENED)
		error = 1;
	if (error_flag == ERROR_RESET)
		error = 0;
	return (error);
}

void	*ft_abort(void *buffer)
{
	free(buffer);
	return (NULL);
}
