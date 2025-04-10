/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_qts_analyze.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-10 23:20:11 by carlaugu          #+#    #+#             */
/*   Updated: 2025-04-10 23:20:11 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expand.h"

static int	check_token_context_details(t_word **word, t_data *data);

int	analyze_token_context(t_word **word, t_data *data)
{
	if (!ft_strcmp((*word)->word, "export"))
		data->exp->export_cmd = true;
	if (is_valid_tilde((*word)->word))
	{
		if (expand_tilde(word, data) == -1)
			return (-1);
	}
	if (check_token_context_details(word, data) == -1)
		return (-1);
	return (0);
}
/* This is an auxiliary function for analyze_token_context */
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
			s = (*word)->word;
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
