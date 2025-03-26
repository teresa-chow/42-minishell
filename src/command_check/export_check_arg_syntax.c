/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_check_arg_syntax.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-26 22:19:39 by carlaugu          #+#    #+#             */
/*   Updated: 2025-03-26 22:19:39 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/errors.h"
#include "../../include/parse.h"
#include "../../include/utils.h"

static int	check_syntax(char *s);

void	check_export_args(t_word *word, t_data *data)
{
	t_word	*tmp;
	t_word	*last_word;

	last_word = word;
	word = word->next;
	while (word)
	{
		if (!check_syntax(word->word))
		{
			error_export_syntax(word->word, data);
			tmp = word;
			last_word->next = word->next;
			word = word->next;
			free(tmp->word);
			tmp->word = NULL;
			free(tmp);
			tmp = NULL;
		}
		else
		{
			last_word = word;
			word = word->next;
		}
	}
}

static int	check_syntax(char *s)
{
	while (*s)
	{
		if ((*s == '+' && *(s + 1) == '=') || *s == '=')
			break ;
		if (!ft_isalnum(*s) && *s != '_')
			return (0);
		s++;
	}
	return (1);
}

int	check_if_has_args(t_word_lst *last_cmd, t_word_lst **curr, t_word_lst **word_lst)
{
	if (!(*curr)->word->next)
	{
		last_cmd->next = (*curr)->next;
		free_words(&(*curr)->word);
		free((*curr));
		if (last_cmd != *curr)
			*curr = last_cmd->next;
		else
		{
			*curr = NULL;
			*word_lst = NULL;
		}
		return (1);
	}
	return (0);
}
