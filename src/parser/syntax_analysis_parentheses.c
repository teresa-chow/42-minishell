/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analysis_parentheses.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:51:30 by tchow-so          #+#    #+#             */
/*   Updated: 2025/04/03 11:30:55 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/utils.h"
#include "../../include/errors.h"

static int	check_nest_lvl(char *word, int i);
static int	rec_syntax_analysis(char *word);
static int	check_parentheses(char *word);
static int	check_nests(char *word);

//TODO: memory alloc failure unhandled + tmp_group == '\0'
int	check_group(char *word)
{
	if (check_parentheses(word) != 0)
		return (ERR_BI);
	if (check_nests(word) != 0)
		return (ERR_BI);
	if (rec_syntax_analysis(word) != 0)
		return (ERR_BI);
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

static int	check_nests(char *word)
{
	int	i;

	i = 0;
	while (word[i])
	{
		if (word[i] && word[i] == '(')
		{
			if (check_nest_lvl(word, i) != 0)
				return (ERR_BI);
		} 
		if (word[i])
			i++;
	}
	return (0);
}

static int	check_nest_lvl(char *word, int i)
{
	int	op;

	op = 0;
	while (word[i])
	{
		if (word[i] == '(')
		{
			if (check_nest_lvl(word, ++i) != 0)
				return (-1);
		}
		if (word[i] == ')' && !op)
			return (err_syntax(")"));
		while (word[++i] && word[i] != '(' && word[i] != ')')
		{
			if ((word[i - 1] == '|') && (word[i] == '|'))
				op = 1;
			else if ((word[i - 1] == '&') && (word[i] == '&'))
				op = 1;
		}
		if (word[i] == ')' && !op)
			return (err_syntax(")"));
	}
	return (0);
}

static int	rec_syntax_analysis(char *word)
{
	char		*tmp_group;
	char		**cmd_lst;
	t_word_lst	*tmp_lst;

	if (word[0] == '(')
	{
		tmp_group = ft_substr(word, 1, group_len(word, 0) - 2);
		cmd_lst = tokenize_op(tmp_group);
		if (cmd_lst)
		{
			free(tmp_group);
			tmp_lst = ft_calloc(1, sizeof(t_word_lst));
			if (!tmp_lst)
				return (-1);
			tokenize_w_lst(cmd_lst, tmp_lst);
			free_strarray(cmd_lst);
			if (tmp_lst->word && syntax_analysis(tmp_lst) != 0)
			{
				free_word_lst(&tmp_lst);
				return (ERR_BI);
			}
			free_word_lst(&tmp_lst);
		}
	}
	return (0);
}
