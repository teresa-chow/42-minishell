/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_qts_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-07 15:24:14 by carlaugu          #+#    #+#             */
/*   Updated: 2025-04-07 15:24:14 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expand.h"

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
/* Used to check is we have to handle with arg or not*/
void	analyze_token_context(char *s, t_data *data)
{
	if (!ft_strcmp(s, "export"))
		data->exp->export_cmd = true;
	while (*s)
	{
		if (*s == '\'' && !data->exp->has_sing)
			data->exp->has_sing = !data->exp->has_sing;
		else if (*s == '"' && !data->exp->has_dbl)
			data->exp->has_dbl = !data->exp->has_dbl;
		else if (*s == '$' && is_valid_dollar(s) && !data->exp->has_exp)
			data->exp->has_exp = !data->exp->has_exp;
		s++;
	}
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
/* Find the next quote if we are in or out of quotes 
and check if has dollar sign between */
char	*get_next_qt(char *s, t_data *data)
{
	while (*s)
	{
		if (*s == '$' && is_valid_dollar(s) && !data->exp->to_exp && !data->exp->in_sing)
			data->exp->to_exp = !data->exp->to_exp;
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
