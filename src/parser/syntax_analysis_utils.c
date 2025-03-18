/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analysis_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so  <tchow-so@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:12:00 by tchow-so          #+#    #+#             */
/*   Updated: 2025/03/17 16:12:00 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/utils.h"
#include "../../include/errors.h"

int	check_logical_op(t_word *word)
{
	char		token[3];

	if (is_operator(word->word[0]))
	{
		if (ft_strlen(word->word) == 1)
		{
			if (word->word[0] == '|')
				return (err_syntax("|"));
		}
		else
		{
			token[0] = word->word[0];
			token[1] = word->word[1];
			token[2] = '\0';
			return (err_syntax(token));
		}
	}
	return (0);
}

int	check_op_syntax(char *word)
{
	int	len;

	len = ft_strlen(word);
	if (len == 3)
		if (word[2] == '|')
			return (err_syntax("|"));
	if (len > 2)
	{
		if (word[0] == '<')
			return (err_syntax("<"));
		else if (word[0] == '>')
			return (err_syntax(">"));
		else if (word[0] == '|')
			return (err_syntax("||"));
		else if (word[0] == '&')
			return (err_syntax("&&"));
	}
	return (0);
}

int	check_redir_seq(t_word_lst *word_lst, t_word *word)
{
	char		token[3];

	if (is_redirection(word->word[0]))
	{
		if (!word->next)
		{
			if (!word_lst->next)
				return (err_syntax("newline"));
			else
				return (check_logical_op(word_lst->next->word));
		}
		else if (is_redirection(word->next->word[0]))
		{
			if (ft_strlen(word->next->word) == 1)
				return (err_syntax(&word->next->word[0]));
			else
			{
				token[0] = word->next->word[0];
				token[1] = word->next->word[1];
				token[2] = '\0';
				return (err_syntax(token));
			}
		}
	}
	return (0);
}

int	is_valid_redir(t_word *word)
{
	int	len;

	len = ft_strlen(word->word);
	if (len == 2 && is_redirection(word->word[0]))
	{
		if (!ft_strcmp(word->word, ">>") || !ft_strcmp(word->word, "<<")
			|| !ft_strcmp(word->word, ">|"))
			return (1);
		else
			return (err_syntax(&word->word[1]));
	}
	return (0);
}
