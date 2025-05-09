/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:11:10 by carlaugu          #+#    #+#             */
/*   Updated: 2024/10/29 11:08:33 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	ft_count_words(char const *str, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == c))
			i++;
		if (str[i] && (str[i] != c))
			count++;
		while (str[i] && (str[i] != c))
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

static	char	**ft_creat_arr(char const *s, char c, char **arr, size_t words)
{
	size_t	i;
	size_t	j;
	size_t	start;

	i = 0;
	j = 0;
	while (i < words)
	{
		start = j;
		while (s[start] && s[start] == c)
			start++;
		j = start;
		while (s[j] && s[j] != c)
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

char	**ft_split(char const *s, char c)
{
	size_t	words;
	char	**array;

	if (!s)
		return (NULL);
	words = ft_count_words(s, c);
	array = malloc ((words + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	return (ft_creat_arr(s, c, array, words));
}
