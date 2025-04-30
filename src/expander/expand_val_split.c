/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_val_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 21:04:57 by carlaugu          #+#    #+#             */
/*   Updated: 2025/04/30 17:20:59 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/expand.h"

static unsigned int	ft_substr_count(char const *s)
{
	unsigned int	i;
	unsigned int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if ((!is_delimiter(s[i]) && is_delimiter(s[i + 1])) 
				|| s[i + 1] == '\0')
			count++;
		i++;
	}
	return (count);
}

static unsigned int	ft_substr_len(char const *s)
{
	unsigned int	i;

	i = 0;
	while (s[i] && !is_delimiter(s[i]))
		i++;
	return (i);
}

static char	**ft_free(char **str, int i)
{
	while (i >= 0)
	{
		free(str[i]);
		i--;
	}
	free(str);
	return (NULL);
}

char	**get_words(char const *s)
{
	char	**str;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	str = malloc((ft_substr_count(s) + 1) * sizeof(char *));
	if (!s || !str)
		return (0);
	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (!is_delimiter(s[i]))
		{
			str[j] = ft_substr(s, i, ft_substr_len(&s[i]));
			if (!str[j])
				return (ft_free(str, j));
			j++;
			i += ft_substr_len(&s[i]);
		}
		else
			i++;
	}
	str[j] = 0;
	return (str);
}
