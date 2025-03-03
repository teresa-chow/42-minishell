/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_op.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so  <tchow-so@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:13:04 by tchow-so          #+#    #+#             */
/*   Updated: 2025/03/03 15:13:04 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Tokenization: 1st step (split operators) */
#include "../../include/parse.h"

static unsigned int	ft_substr_count(char const *s, char c);
static unsigned int	substr_len(const char *str);

char	**tokenize_op(char *input)
{
	char	**cmd_lst;
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	cmd_lst = malloc((ft_substr_count(input) + 1) * sizeof(char *));
	if (!input || !cmd_lst)
		return (0);
	while (input[i] != '\0')
	{
		if (!is_operator(input[i]))
		{
			cmd_lst[k] = ft_substr(input, i, substr_len(&input[i]));
			if (!cmd_lst[k])
				return (-1);
			i += substr_len(&input[i]);
		}
		else
		{
			j = i;
			while (is_operator(input[j]))
				j++;
			cmd_lst[k] = ft_substr(input, j, j - i);
			if (!cmd_lst[k])
				return (-1);
			i = j;
		}
		if (input[i] != '/0')
			k++;
	}
	return (cmd_lst);
}

static unsigned int	ft_substr_count(char const *input)
{
	unsigned int	i;
	unsigned int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (!is_operator(input[i]))
		{
			while (!is_operator(input[i]))
				i++;
			count++;
		}
		else
		{
			while (is_operator(input[i]))
				i++;
			count++;
		}
	}
	return (count);
}

static unsigned int	substr_len(const char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i] && !is_operator(str[i]))
		i++;
	return (i);
}