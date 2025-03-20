/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analysis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:19:00 by tchow-so          #+#    #+#             */
/*   Updated: 2025/03/20 09:17:18 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/utils.h"
#include "../../include/errors.h"

static int	check_syntax(t_word_lst *tmp_lst, t_word *tmp_word);
static int	check_syntax_word(t_word_lst *tmp_lst, t_word *tmp_word);

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
			if (is_operator(tmp_lst->word->word[0])
				&& check_op_syntax(tmp_lst->word->word) == 0)
				{
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
		tmp_word = tmp_word->next;
	}
	return (0);
}

/*
else if (tmp_lst && tmp_lst->next) //check op following op (review order)
{
	if (is_operator(tmp_lst->word->word[0])
		&& !check_op_syntax(tmp_lst->word->word))
	{
		if (check_logical_op(tmp_lst->next->word) != 0)
			return (ERR_BI);
	}
}
*/