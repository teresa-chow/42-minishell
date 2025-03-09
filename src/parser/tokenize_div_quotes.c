/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_div_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so  <tchow-so@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:13:19 by tchow-so          #+#    #+#             */
/*   Updated: 2025/03/05 11:13:19 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

int	handle_quote(char *cmd, int *j, t_word_lst **word_lst, t_word **word) //
{
	init_word(*word_lst, word);
	(*word)->word = ft_substr(cmd, *j, next_quote(cmd, *j, is_quote(cmd[*j])));
	if (!(*word)->word)
		return (-1);
	*j += next_quote(cmd, *j, is_quote(cmd[*j]));
	return (0);
}

unsigned int	next_quote(const char *str, unsigned int start, int	code)
{
	unsigned int	end;

	end = start + 1;
	if (code == 1)
	{
		while (str[end] && (str[end] != '\''))
			end++;
		if (str[end] && (str[end] == '\''))
			end++;
	}
	else if (code == 2)
	{
		while (str[end] && (str[end] != '\"'))
			end++;
		if (str[end] && (str[end] == '\"'))
			end++;
	}
	return (end - start);
}
