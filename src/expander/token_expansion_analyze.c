/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expansion_analyze.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 23:20:11 by carlaugu          #+#    #+#             */
/*   Updated: 2025/04/30 23:57:03 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expand.h"

static int	check_token_context_details(t_word **word, t_data *data);
static int	export_has_exp_bfr_equal(char *s, t_word *word);
static int	expand_oldpwd(t_word *word, t_data *data);

int	analyze_token_context(t_word **word, t_data *data)
{
	if ((*word)->redir == HEREDOC)
	{
		*word = (*word)->next;
		return (0);
	}
	if (data->exp->export_cmd && export_has_exp_bfr_equal((*word)->word , *word))
		data->exp->export_exp_bfr_equal = true;
	check_builtin_name(data, word);
	if (is_valid_tilde((*word)->word))
	{
		if (expand_tilde(word, data) == -1)
			return (-1);
		return (0);
	}
	if (data->exp->cd_cmd && !ft_strcmp((*word)->word, "-"))
	{
		data->has_hifen = true;
		if (expand_oldpwd(*word, data) == 1)
			return (-1);
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
			break ;
		}
		if (*s == '\'' && !data->exp->has_sing)
			data->exp->has_sing = true;
		else if (*s == '"' && !data->exp->has_dbl)
			data->exp->has_dbl = true;
		else if (*s == '$' && is_valid_dollar(s) && !data->exp->has_exp)
		{
				if (data->exp->export_cmd)
				(*word)->literal = true;
			data->exp->has_exp = true;
		}
		s++;
	}
	return (0);
}

static int	export_has_exp_bfr_equal(char *s, t_word *word)
{
	char	*equal;

	equal = ft_strchr(s, '=');
	if (equal)
	{
		if (*(equal + 1) == '\'' || *(equal + 1) == '"')
			word->in_quote = *(equal + 1);
		while (s != equal)
		{
			if (*s == '$' && is_valid_dollar(s + 1))
				return (1);
			s++;
		}
	}
	return (0);
}

static int	expand_oldpwd(t_word *word, t_data *data)
{
	t_env_node	*var;

	var = ft_getenv(data->env, "OLDPWD");
	if (!var || !var->val)
		return (0);
	if (var->val)
	{
		free(word->word);
		word->word = ft_strdup(var->val);
		if (!word->word)
			return (-1);
	}
	return (0);
}
