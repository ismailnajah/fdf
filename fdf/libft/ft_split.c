/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:53:37 by inajah            #+#    #+#             */
/*   Updated: 2024/11/29 09:09:58 by inajah           ###   ########.fr       */
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

char	**ft_split_free(char **list_words)
{
	int	i;

	i = 0;
	while (list_words[i])
	{
		free(list_words[i]);
		list_words[i] = NULL;
		i++;
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
				return (ft_split_free(list_words));
			index++;
		}
	}
	return (list_words);
}

int	ft_split_count(char **words)
{
	int	i;

	i = 0;
	while (words[i] && words[i][0] != '\n')
		i++;
	return (i);
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
