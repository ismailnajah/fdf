/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 11:24:48 by inajah            #+#    #+#             */
/*   Updated: 2024/11/13 14:46:06 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*get_line_buffer(char *static_buffer)
{
	char	*new_line;
	int		i;

	if (!static_buffer[0])
		return (NULL);
	i = 0;
	while (static_buffer[i] && static_buffer[i] != '\n')
		i++;
	if (static_buffer[i] == '\n')
		i++;
	new_line = (char *)malloc((i + 1) * sizeof(char));
	if (!new_line)
		return (NULL);
	new_line[i] = '\0';
	if (!new_line)
		return (NULL);
	i = 0;
	while (static_buffer[i] && static_buffer[i] != '\n')
	{
		new_line[i] = static_buffer[i];
		i++;
	}
	if (static_buffer[i] && static_buffer[i] == '\n')
		new_line[i] = '\n';
	return (new_line);
}

static char	*ft_extend_str(char *str, char *ext)
{
	char	*out;

	out = ft_strjoin(str, ext);
	free(str);
	return (out);
}

static char	*ft_delete_line(char *old_buffer)
{
	char	*new_buffer;
	int		buff_len;
	int		i;
	int		j;

	i = 0;
	buff_len = ft_strlen(old_buffer);
	while (old_buffer[i] && old_buffer[i] != '\n')
		i++;
	if (!old_buffer[i])
		return (ft_abort(old_buffer));
	new_buffer = (char *)malloc((buff_len - i + 1) * sizeof(char));
	if (!new_buffer)
		return (ft_abort(old_buffer));
	i++;
	j = 0;
	while (old_buffer[i])
		new_buffer[j++] = old_buffer[i++];
	new_buffer[j] = '\0';
	free(old_buffer);
	return (new_buffer);
}

static char	*ft_read_lines(int fd, char *static_buffer)
{
	char	*buffer;
	int		bytes_read;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (ft_abort(static_buffer));
	buffer[0] = '\0';
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(buffer, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			free(static_buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		if (bytes_read > 0)
			static_buffer = ft_extend_str(static_buffer, buffer);
	}
	free(buffer);
	return (static_buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*new_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer)
	{
		buffer = (char *)malloc(sizeof(char));
		if (!buffer)
			return (NULL);
		buffer[0] = '\0';
	}
	buffer = ft_read_lines(fd, buffer);
	if (!buffer)
		return (NULL);
	new_line = get_line_buffer(buffer);
	if (!new_line)
	{
		buffer = ft_abort(buffer);
		return (NULL);
	}
	buffer = ft_delete_line(buffer);
	return (new_line);
}
