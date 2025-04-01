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

int	find_expand(t_word *word, t_data *data)
{
	char	*tmp;

	while (word)
	{
		tmp =word->word;
		while (*tmp)
		{
			if (*tmp == '$')
			{
				if (expand(data, word) == -1)
					return (-1);
				break;
			}
			tmp++;
		}
		word = word->next;
	}
	return (0);
}
char	*find_last_sign(char *arg)
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