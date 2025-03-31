/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analysis_parentheses2.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:12:00 by tchow-so          #+#    #+#             */
/*   Updated: 2025/03/31 17:15:44 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/utils.h"
#include "../../include/errors.h"

static int	nest_lvl_inner(char *word, int i);
static int	nest_lvl_outer(char *word, int i, int lvl, int depth);

int	check_nest_lvl(char *word, int i, int lvl, int depth)
{
	if (lvl < depth)
		return (nest_lvl_outer(word, i, lvl, depth));
	if (lvl == depth)
		return (nest_lvl_inner(word, i));
	return (0);
}

static int	nest_lvl_outer(char *word, int i, int lvl, int depth)
{
	int	op;

	op = 0;
	while (word[i])
	{
		if (word[i] == '(')
		{
			if (nest_lvl_outer(word, ++i, ++lvl, depth) != 0)
				return (-1);
		}
		else if (word[i] == ')')
			lvl--;
		while (word[++i] && word[i] != '(' && word[i] != ')')
		{
			if (lvl < depth && word[i] == '|')
				op = 1;
			else if (lvl < depth && (word[i - 1] == '&') && (word[i] == '&'))
				op = 1;
		}
		if (lvl < depth && word[i] == ')' && !op)
			return (err_syntax(")"));
	}
	return (0);
}

static int	nest_lvl_inner(char *word, int i)
{
	++i;
	if (word[i] == ')')
		return (err_syntax(")"));
	return (0);
}
