/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_qts_checkers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-10 22:48:01 by carlaugu          #+#    #+#             */
/*   Updated: 2025-04-10 22:48:01 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expand.h"

/* Find the next quote if we are in or out of quotes 
and check if has dollar sign between */
char	*find_next_quote_and_parse(char *s, t_data *data)
{
	char	first_char;

	first_char = *s;
	while (*s)
	{
		if (data->exp->export_cmd && *s == '=' && first_char != '=')
			data->exp->export_after_equal = true;
		if (*s == '$' && is_valid_dollar(s) && !data->exp->in_sing)
			data->exp->to_exp = true;
		if (*s == '\'' && data->exp->in_sing)
			break;
		else if (*s == '"' && data->exp->in_dbl)
			break;
		else if ((*s == '\'' || *s == '"') && !data->exp->in_dbl && !data->exp->in_sing)
			break;
		s++;
	}
	return (s);
}

/* Find invalid char in var name */
char	*find_non_alnum(char *s)
{
	if (*s == '?')
		return (s + 1);
	while (*s)
	{
		if (!ft_isalnum(*s))
			break;
		s++;
	}
	return (s);
}

/* Used to expand when no quotes */
int	has_delimiter(char *s)
{
	while (*s)
	{
		if (*s == ' ' && *(s + 1) == ' ')
			return (1);
		else if (*s == ' ' && is_delimiter(*(s +1)))
			return (1);
		else if (is_delimiter(*s))
			return (1);
		s++;
	}
	return (0);
}
/* Used to check if is a valid var name */
int	is_valid_dollar(char *s)
{
	if (*(s + 1) == '?' || ft_isalnum(*(s + 1)))
		return (1);
	return (0);
}

bool	is_valid_tilde(char *s)
{
	if (*s == '~' && !*(s + 1))
		return (true);
	return (false);
}
