/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_div_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:13:19 by tchow-so          #+#    #+#             */
/*   Updated: 2025/04/10 09:10:06 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

int	handle_quote(char *cmd, int *j, t_word_lst **word_lst, t_word **word)
{
	char	*quote;

	quote = NULL;
	if (is_quote(cmd[*j]))
	{
		quote = ft_substr(cmd, *j, next_quote(cmd, *j, is_quote(cmd[*j])));
		if (!quote)
			return (-1);
		if (!cmd[*j - 1] || is_delimiter(cmd[*j - 1]))
		{
			init_word(*word_lst, word);
			(*word)->word = quote;
			*j += next_quote(cmd, *j, is_quote(cmd[*j]));
		}
		else
		{
			(*word)->word = ft_strjoin((*word)->word, quote);
			if (!(*word)->word)
				return (-1);
			*j += next_quote(cmd, *j, is_quote(cmd[*j]));
		}
	}
	return (0);
}

unsigned int	next_quote(const char *str, unsigned int start, int code)
{
	unsigned int	end;

	end = start + 1;
	if (code == 1)
	{
		while (str[end] && (str[end] != '\''))
			++end;
		if (str[end] && (str[end] == '\''))
			++end;
		while (str[end] && !is_delimiter(str[end]) && str[end] != '\''
			&& str[end] != '(' && str[end] != ')')
			++end;
	}
	else if (code == 2)
	{
		while (str[end] && (str[end] != '\"'))
			++end;
		if (str[end] && (str[end] == '\"'))
			++end;
		while (str[end] && !is_delimiter(str[end]) && str[end] != '\"'
			&& str[end] != '(' && str[end] != ')')
			++end;
	}
	return (end - start);
}
