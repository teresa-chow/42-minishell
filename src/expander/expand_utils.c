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
#include "../../include/expand.h"
#include "../../include/utils.h"

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
char	find_extra_var_name(char *arg)
{
	if (*arg == '?' && *get_valid_dollar(arg))
		return (0);
	else if (*arg == '?')
		return (*(arg + 1));
	while (*arg)
	{
		if (!ft_isalnum(*arg))
			break;
		arg++;
	}
	return (*arg);
}

char	*get_valid_dollar(char*arg)
{
	while (*arg)
	{
		if (*arg == '$' && (ft_isalnum(*(arg + 1)) || *(arg + 1) == '?'))
			break;
		arg++;
	}
	return (arg);
}

int	count_begin_quotes(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] != '"')
			break;
	}
	return (i);
}

int	count_end_quotes(char *s)
{
	int	i;

	s = ft_strchr(get_last_exp(s), '"');
	if (!s)
		return (0);
	i = -1;
	while (s[++i])
	{
		if (s[i] != '"')
			break;
	}
	return (i);
}
