/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:53:37 by inajah            #+#    #+#             */
/*   Updated: 2024/11/05 13:53:37 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

static char	**free_previous(char **list_words, int index)
{
	while (index >= 0)
	{
		free(list_words[index]);
		list_words[index] = NULL;
		index--;
	}
	free(list_words);
	return (NULL);
}

static char	**populate_list_words(char **list_words, char const *s, char c)
{
	size_t	index;
	size_t	i;
	size_t	start;

	index = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			start = i;
			while (s[i] && s[i] != c)
				i++;
			list_words[index] = ft_substr(s, start, i - start);
			if (!list_words[index])
				return (free_previous(list_words, index - 1));
			index++;
		}
	}
	return (list_words);
}

char	**ft_split(char const *s, char c)
{
	int		nb_words;
	char	**list_words;

	if (!s)
		return (NULL);
	nb_words = count_words(s, c);
	list_words = (char **)ft_calloc((nb_words + 1), sizeof(char *));
	if (!list_words)
		return (NULL);
	return (populate_list_words(list_words, s, c));
}
