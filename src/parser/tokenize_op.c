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

#include "../../include/parse.h"
#include "../../include/utils.h"

static unsigned int	substr_count(char const *s);
static unsigned int	substr_len(const char *str);

/* Tokenization (1): divide cmd and operators */
char	**tokenize_op(char *input)
{
	char	**cmd_lst;
	int	i;
	int	j;

	i = 0;
	j = 0;
	cmd_lst = malloc((substr_count(input) + 1) * sizeof(char *));
	if (!input || !cmd_lst)
		return (0);
	while (input[i] != '\0')
	{
		cmd_lst[j] = ft_substr(input, i, substr_len(&input[i]));
		if (!cmd_lst[j])
		{
			free_strarray(cmd_lst);
			return (NULL);
		}
		j++;
		i += substr_len(&input[i]);
	}
	cmd_lst[j] = 0;
	free(input);
	return (cmd_lst);
}

static unsigned int	substr_count(char const *input)
{
	unsigned int	i;
	unsigned int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (input[i] && !is_operator(input[i]))
		{
			count++;
			while (input[i])
			{
				if (is_operator(input[i]))
					break ;
				if (is_quote((int)input[i]))
					i += next_quote(input, i, is_quote((int)input[i]));
				else
					i++;
			}
		}
		else
		{
			count++;
			while (input[i] && is_equal_next(input, i))
				i++;
			i++;
		}
	}
	return (count);
}

static unsigned int	substr_len(const char *str)
{
	unsigned int	i;

	i = 0;
	if (!is_operator(str[i]))
	{
		while (str[i])
		{
			if (is_operator(str[i]))
					break ;
			if (is_quote((int)str[i]))
				i += next_quote(str, i, is_quote((int)str[i]));
			else
				i++;
		}
	}
	else
	{
		while (str[i] && is_equal_next(str, i))
			i++;
		i++;
	}
	return (i);
}