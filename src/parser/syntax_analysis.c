/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analysis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:19:00 by tchow-so          #+#    #+#             */
/*   Updated: 2025/03/28 10:35:10 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/utils.h"
#include "../../include/errors.h"

#include "../../tests/test.h"

static int	check_syntax(t_word_lst *tmp_lst, t_word *tmp_word);
static int	check_syntax_word(t_word_lst *tmp_lst, t_word *tmp_word);
static int	check_group(char *word);
static int	check_parentheses(char *word);

int	syntax_analysis(t_word_lst *word_lst)
{
	t_word_lst	*tmp_lst;
	t_word		*tmp_word;

	tmp_lst = word_lst;
	tmp_word = word_lst->word;
	if (check_logical_op(tmp_word) != 0)
		return (ERR_BI);
	if (check_syntax(tmp_lst, tmp_word) != 0)
		return (ERR_BI);
	return (0);
}

static int	check_syntax(t_word_lst *tmp_lst, t_word *tmp_word)
{
	while (tmp_lst)
	{
		tmp_word = tmp_lst->word;
		if (check_syntax_word(tmp_lst, tmp_word) != 0)
			return (ERR_BI);
		tmp_lst = tmp_lst->next;
		if (tmp_lst && !tmp_lst->next)
		{
			if (check_logical_op(tmp_lst->word) != 0)
				return (ERR_BI);
		}
		else if (tmp_lst && tmp_lst->next)
		{
			if (is_operator(tmp_lst->word->word[0]))
			{
				if (check_op_syntax(tmp_lst->word->word) != 0)
					return (ERR_BI);
				if (check_logical_op(tmp_lst->next->word) != 0)
					return (ERR_BI);
			}
		}
	}
	return (0);
}

static int	check_syntax_word(t_word_lst *tmp_lst, t_word *tmp_word)
{
	while (tmp_word)
	{
		if (is_operator(tmp_word->word[0])
			|| is_redirection(tmp_word->word[0]))
		{
			if (check_op_syntax(tmp_word->word) != 0)
				return (ERR_BI);
			if (is_valid_redir(tmp_word) > 1)
				return (ERR_BI);
			if (check_redir_seq(tmp_lst, tmp_word) != 0)
				return (ERR_BI);
		}
		else
		{
			if (check_quotes(tmp_word->word) != 0)
				return (ERR_BI);
			if (check_group(tmp_word->word) != 0)
				return (ERR_BI);
		}
		tmp_word = tmp_word->next;
	}
	return (0);
}

static int	check_group(char *word) // memory alloc failure unhandled
{
	char		*tmp_group;
	char 		**cmd_lst;
	t_word_lst	*tmp_lst;
	int			i;

	i = 0;
	if (check_parentheses(word) != 0)
		return (ERR_BI);
	if (word[i] == '(')
	{
		tmp_group = ft_substr(word, i + 1, group_len(word, i) - 2);
		cmd_lst = tokenize_op(tmp_group);
		if (cmd_lst)
		{
			tmp_lst = ft_calloc(1, sizeof(t_word_lst));
			if (!tmp_lst)
				return (-1);
			tokenize_w_lst(cmd_lst, tmp_lst);
			if (syntax_analysis(tmp_lst) != 0)
				return (ERR_BI);
			free_strarray(cmd_lst);
			free_word_lst(&tmp_lst);
		}
	}
	return (0);
}

static int	check_parentheses(char *word)
{
	int			i;
	int			open;
	int			closed;

	i = -1;
	open = 0;
	closed = 0;
	while (word[++i])
	{
		if (is_quote(word[i]))
			i += next_quote(word, i, is_quote(word[i]));
		if (word[i] == '(')
			open++;
		else if (word[i] == ')')
			closed++;
	}
	if (open > closed)
		return (err_syntax("newline"));
	else if (open < closed)
		return (err_syntax(")"));
	return (0);
}
