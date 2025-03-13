/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_div_redirect.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so  <tchow-so@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:26:29 by tchow-so          #+#    #+#             */
/*   Updated: 2025/03/13 10:26:29 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

static unsigned int	substr_len(const char *str, unsigned int start);

int	handle_redirection(char *cmd, int *j, t_word_lst **word_lst, t_word **word)
{
	if (is_redirection(cmd[*j]))
	{
		init_word(*word_lst, word);
		(*word)->word = ft_substr(cmd, *j, substr_len(cmd, *j));
		if (!(*word)->word)
			return (-1);
		*j += substr_len(cmd, *j);
	}
	return (0);
}

static unsigned int	substr_len(const char *str, unsigned int start)
{
	unsigned int	end;
	unsigned int	len;

	end = start;
	while (is_redirection(str[end]) || str[end] == '|')
		end++;
	len = end - start;
	return (len);
}
