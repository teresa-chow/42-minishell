/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expansion_analyze.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 23:20:11 by carlaugu          #+#    #+#             */
/*   Updated: 2025/04/17 15:42:50 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expand.h"

static int	check_token_context_details(t_word **word, t_data *data);
static int	export_has_exp_bfr_equal(char *s);

int	analyze_token_context(t_word **word, t_data *data)
{
	if (data->exp->export_cmd && export_has_exp_bfr_equal((*word)->word))
		data->exp->export_exp_bfr_equal = true;
	if (!ft_strcmp((*word)->word, "export"))
		data->exp->export_cmd = true;
	if (is_valid_tilde((*word)->word))
	{
		if (expand_tilde(word, data) == -1)
			return (-1);
		return (0);
	}
	if (check_token_context_details(word, data) == -1)
		return (-1);
	return (0);
}

static int	check_token_context_details(t_word **word, t_data *data)
{
	char	*s;

	s = (*word)->word;
	while (*s)
	{
		if (data->exp->export_cmd && *s == '=' && is_valid_tilde(s + 1))
		{
			data->exp->til_aft_equal = true;
			if (expand_tilde(word, data) == -1)
				return (-1);
			data->exp->til_aft_equal = false;
			break;
		}
		if (*s == '\'' && !data->exp->has_sing)
			data->exp->has_sing = true;
		else if (*s == '"' && !data->exp->has_dbl)
			data->exp->has_dbl = true;
		else if (*s == '$' && is_valid_dollar(s) && !data->exp->has_exp)
			data->exp->has_exp = true;
		s++;
	}
	return (0);
}

static int	export_has_exp_bfr_equal(char *s)
{
	char	*equal;

	equal = ft_strchr(s, '=');
	if (equal)
	{
		while (s != equal)
		{
			if (*s == '$' && is_valid_dollar(s + 1))
				return (1);
			s++;
		}
	}
	return (0);
}
