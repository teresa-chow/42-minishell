/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_div_general.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:58:16 by tchow-so          #+#    #+#             */
/*   Updated: 2025/03/20 09:12:20 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

static unsigned int	substr_len(const char *str, unsigned int start);

int	handle_other(char *cmd, int *j, t_word_lst **word_lst, t_word **word)
{
	if (cmd[*j] && !is_delimiter(cmd[*j]) && !is_quote(cmd[*j])
		&& !is_redirection(cmd[*j]) && cmd[*j] != '(')
	{
		init_word(*word_lst, word);
		(*word)->word = ft_substr(cmd, *j, substr_len(cmd, *j));
		if (!(*word)->word)
			return (-1);
		*j += substr_len(cmd, *j);
	}
	return (0);
}

int	init_word(t_word_lst *word_lst, t_word **word)
{
	if (!*word)
	{
		*word = ft_calloc(1, sizeof(t_word)); //TODO: handle mem_alloc err
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
	return (0);
}

int	add_word(t_word **word_desc)
{
	t_word	*new;

	new = ft_calloc(1, sizeof(t_word));
	if (!new)
		return (-1);
	new->next = NULL;
	(*word_desc)->next = new;
	*word_desc = (*word_desc)->next;
	return (0);
}

int	add_word_lst(t_word_lst **word_lst)
{
	t_word_lst	*new;

	new = ft_calloc(1, sizeof(t_word_lst));
	if (!new)
		return (-1);
	new->next = NULL;
	(*word_lst)->next = new;
	*word_lst = (*word_lst)->next;
	return (0);
}

static unsigned int	substr_len(const char *str, unsigned int start)
{
	unsigned int	end;
	unsigned int	len;

	end = start;
	while (str[end] && !is_delimiter(str[end])
		&& !is_redirection(str[end]) && str[end] != '(')
		end++;
	len = end - start;
	return (len);
}
