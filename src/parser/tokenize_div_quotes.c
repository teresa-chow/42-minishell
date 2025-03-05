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

static unsigned int	next_quote(const char *str, unsigned int start, int	code);

int	handle_quote(char *cmd, int *j, t_word_lst *word_lst, t_word **word) //
{
	if (!*word)
	{
		*word = malloc(sizeof(t_word)); //TODO: handle mem_alloc err
		if (!*word)
		{
			word_lst = NULL;
			return (-1);
		}
		(*word)->next = NULL;
		word_lst->word = *word;
	}
	else
	{
		if (add_word(word) == -1) //TODO: handle mem_alloc err
			return (-1);
	}
	(*word)->word = ft_substr(cmd, *j, next_quote(cmd, *j, is_quote(cmd[*j])));
	if (!(*word)->word)
		return (-1);
	*j += next_quote(cmd, *j, is_quote(cmd[*j]));
	return (0);
}

static unsigned int	next_quote(const char *str, unsigned int start, int	code)
{
	unsigned int	end;
	unsigned int	len;

	end = start + 1;
	if (code == 1)
	{
		while (str[end] && (str[end] != '\''))
			end++;
	}
	else if (code == 2)
	{
		while (str[end] && (str[end] != '\"'))
			end++;
	}
	if (str[end])
		end++;
	len = end - start;
	return (len);
}
