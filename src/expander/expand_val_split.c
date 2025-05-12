/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_val_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 21:04:57 by carlaugu          #+#    #+#             */
/*   Updated: 2025/04/30 23:54:55 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/expand.h"

#include "../../include/parse.h"
#include "../../include/expand.h"

static	size_t	ft_count_words(char const *str)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if ((!is_delimiter(str[i]) && is_delimiter(str[i + 1]))
			|| str[i + 1] == '\0')
			count++;
		i++;
	}
	return (count);
}

static	void	ft_free(char **arr, size_t i)
{
	size_t	j;

	j = 0;
	while (j < i)
	{
		free(arr[j]);
		j++;
	}
	free(arr);
}

static	char	**ft_creat_arr(char const *s, char **arr, size_t words)
{
	size_t	i;
	size_t	j;
	size_t	start;

	i = 0;
	j = 0;
	while (i < words)
	{
		start = j;
		while (s[start] && is_delimiter(s[start]))
			start++;
		j = start;
		while (s[j] && !is_delimiter(s[j]))
			j++;
		arr[i] = ft_substr(s, start, j - start);
		if (!arr[i])
		{
			ft_free(arr, i);
			return (NULL);
		}
		i++;
	}
	arr[words] = 0;
	return (arr);
}

char	**get_words(char const *s)
{
	size_t	words;
	char	**array;

	if (!s)
		return (NULL);
	words = ft_count_words(s);
	array = malloc ((words + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	return (ft_creat_arr(s, array, words));
}
