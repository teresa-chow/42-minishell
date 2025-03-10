/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_div_parentheses.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so  <tchow-so@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:13:19 by tchow-so          #+#    #+#             */
/*   Updated: 2025/03/05 11:13:19 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

static unsigned int	group_len(const char *str, unsigned int start);

int handle_parentheses(char *cmd, int *j, t_word_lst **word_lst, t_word **word)
{
	init_word(*word_lst, word);
	(*word)->word = ft_substr(cmd, *j, group_len(cmd, *j));
	if (!(*word)->word)
		return (-1);
	*j += group_len(cmd, *j);
	return (0);
}

static unsigned int	group_len(const char *str, unsigned int start)
{
	unsigned int	end;
	unsigned int	len;

	end = start;
	while (str[end] && str[end] != ')')
		end++;
	if (str[end] == ')')
		end ++;
	len = end - start;
	return (len);
}
