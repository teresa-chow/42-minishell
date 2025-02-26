/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so  <tchow-so@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:11:33 by tchow-so          #+#    #+#             */
/*   Updated: 2025/02/25 15:13:19 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

static unsigned int	substr_count(const char *str);
static unsigned int	substr_len(const char *str);
static char	**free_array(char **str, int i);
static int	ft_isspace(int c);

char	**tokenizer(const char *input)
{
	char	**tokens;
	int		i;
	int		j;

	tokens = malloc((substr_count(input) + 1) * sizeof(char *));
	if (!input || !tokens)
		return (0);
	i = 0;
	j = 0;
	while (input[i] != '\0')
	{
		if (!ft_isspace(input[i]))
		{
			tokens[j] = ft_substr(input, i, substr_len(&input[i]));
			if (!tokens[j])
				return (free_array(tokens, j));
			j++;
			i += substr_len(&input[i]);
		}
		else
			i++;
	}
	tokens[j] = 0;
	return (tokens);
}

static unsigned int	substr_count(const char *str)
{
	unsigned int	i;
	unsigned int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if ((!ft_isspace(str[i]) && (ft_isspace(str[i + 1])))
            || str[i + 1] == '\0')
			count++;
		i++;
	}
	return (count);
}

static unsigned int	substr_len(const char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i] && !ft_isspace(str[i]))
		i++;
	return (i);
}

static char	**free_array(char **str, int i)
{
	while (i >= 0)
	{
		free(str[i]);
		i--;
	}
	free(str);
	return (NULL);
}

static int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}
