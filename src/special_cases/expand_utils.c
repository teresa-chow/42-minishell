/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:01:14 by carlaugu          #+#    #+#             */
/*   Updated: 2025/04/03 15:06:21 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/errors.h"
#include "../../include/special_cases.h"
#include "../../include/utils.h"

int	find_expand(t_word *word, t_data *data)
{
	char	*tmp;

	while (word)
	{
		tmp =word->word;
		while (*tmp)
		{
			if (*tmp == '$' && (ft_isalnum(*(tmp + 1)) || *(tmp + 1) == '?'))
			{
				if (expand(data, word) == -1)
					return (-1);
				break;
			}
			tmp++;
		}
		free_exp(data, word, 0);
		word = word->next;
	}
	return (0);
}
char	*get_last_exp(char *arg)
{
	char	*last;

	while (*arg)
	{
		if (*arg == '$' && (ft_isalnum(*(arg + 1)) || *(arg + 1) == '?'))
			last = arg;
		arg++;
	}
	return (last);
}
char	find_extra(char *arg)
{
	if (*arg == '?' && *(arg + 1) == '?')
		return (*(arg + 2));
	else if (*arg == '?' && !*(arg + 1))
		return (0);
	while (*arg)
	{
		if (!ft_isalnum(*arg) && *arg != '?')
			break;
		arg++;
	}
	return (*arg);
}

int	has_delimiter(char *arg)
{
	if (!arg)
		return (0);
	while (*arg)
	{
		if (is_delimiter(*arg))
		{
			if ((*arg == ' ' && (is_delimiter(*(arg + 1)))) || *arg != ' ')
				return (1);
		}
		arg++;
	}
	return (0);
}