/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_checkers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 22:48:01 by carlaugu          #+#    #+#             */
/*   Updated: 2025/04/30 17:30:23 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expand.h"

/* Find the next quote if we are in or out of quotes 
and check if has dollar sign between */
char	*find_next_quote_and_parse(char *s, t_data *data)
{
	char	first_char;

	first_char = *s;
	if (*s == '\'' || *s == '"')
		s++;
	while (*s)
	{
		if (data->exp->export_cmd && *s == '=' && first_char != '=')
			data->exp->export_has_equal = true;
		if (*s == '$' && is_valid_dollar(s) && !data->exp->in_sing)
			data->exp->to_exp = true;
		if (*s == '\'' && data->exp->in_sing)
			return (s + 1); //break;
		else if (*s == '"' && data->exp->in_dbl)
			return (s + 1); //break;
		else if ((*s == '\'' || *s == '"') && !data->exp->in_dbl && !data->exp->in_sing)
			break;
		s++;
	}
	return (s);
}

/* Find invalid char in env var name */
char	*find_non_alnum(char *s)
{
	if (*s == '?')
		return (s + 1);
	while (*s)
	{
		if (!ft_isalnum(*s) && *s != '_')
			break;
		s++;
	}
	return (s);
}

bool	has_delimiter(char *s)
{
	while (*s)
	{
		if (is_delimiter(*s))
			return (true);
		s++;
	}
	return (false);
}
/* Used to check if is a valid var name */
bool	is_valid_dollar(char *s)
{
	if (*(s + 1) == '?' || ft_isalnum(*(s + 1)) || *(s + 1) == '_')
		return (true);
	return (false);
}

bool	is_valid_tilde(char *s)
{
	if (*s == '~' && ((!*(s + 1)) || *(s + 1) == '/'))
		return (true);
	return (false);
}
