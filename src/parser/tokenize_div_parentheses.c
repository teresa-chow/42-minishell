/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_div_parentheses.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:13:19 by tchow-so          #+#    #+#             */
/*   Updated: 2025/03/18 16:21:19 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

int	handle_parentheses(char *cmd, int *j, t_word_lst **word_lst, t_word **word)
{
	unsigned int	len;

	len = 0;
	if (cmd[*j] == '(')
	{
		init_word(*word_lst, word);
		len = group_len(cmd, *j);
		(*word)->word = ft_substr(cmd, *j, len);
		if (!(*word)->word)
			return (-1);
		*j += len;
	}
	return (0);
}

unsigned int	group_len(const char *str, unsigned int start)
{
	unsigned int	end;
	unsigned int	len;

	end = start;
	while (str[end] && str[end] != ')')
	{
		end++;
		if (is_quote(str[end]))
			end += next_quote(str, end, is_quote(str[end]));
		while (str[end] == '(')
			end += group_len(str, end);
	}
	if (str[end] == ')')
		end++;
	len = end - start;
	return (len);
}
