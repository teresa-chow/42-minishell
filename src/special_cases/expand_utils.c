/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:01:14 by carlaugu          #+#    #+#             */
/*   Updated: 2025/04/01 12:09:02 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/errors.h"
#include "../../include/special_cases.h"
#include "../../include/utils.h"

int	free_exp_data(t_data *data, t_word *word, int i)
{
	if (data->exp)
	{
		if (data->exp->bfr && data->exp->bfr != word->word)
			free(data->exp->bfr);
		if (data->exp->mid)
			free(data->exp->mid);
		if (data->exp->aft && data->exp->aft != word->word)
			free(data->exp->aft);
		if (data->exp->buf)
			free(data->exp->buf);
		if (data->exp->extra)
			free(data->exp->extra);
		if (data->exp->arr)
			free_strarray(data->exp->arr);
		if (data->exp->words)
			free_strarray(data->exp->words);
		free(data->exp);
		data->exp = NULL;
		if (i)
			return (error_allocation(data));
	}
	return (0);
}

int	find_expand(t_word *word, t_data *data)
{
	char	*tmp;

	while (word)
	{
		tmp =word->word;
		while (*tmp)
		{
			if (*tmp == '$' && ft_isalnum(*(tmp + 1)))
			{
				if (expand(data, word) == -1)
					return (-1);
				break;
			}
			tmp++;
		}
		free_exp_data(data, word, 0); //////
		word = word->next;
	}
	return (0);
}
char	*get_last_exp(char *arg)
{
	char	*last;

	while (*arg)
	{
		if (*arg == '$')
			last = arg;
		arg++;
	}
	return (last);
}
char	find_no_alnum(char *arg)
{
	while (*arg)
	{
		if (!ft_isalnum(*arg) && *arg != '$')
			break;
		arg++;
	}
	return (*arg);
}