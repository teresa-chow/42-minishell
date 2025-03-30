/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-30 18:14:28 by carlaugu          #+#    #+#             */
/*   Updated: 2025-03-30 18:14:28 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include "../../include/errors.h"
#include "../../include/special_cases.h"

int	analyze_arg(char *arg, t_data *data)
{
	int	has_quotes;

	has_quotes = 0;
	while (*arg)
	{
		if (*arg == '"')
			has_quotes = 1;
		if (*arg == '$' && *(arg + 1))
		{
			data->exp_data = ft_calloc(sizeof(t_expand), sizeof(char));
			if (!data->exp_data)
			{
				if (data->exp_data)
					// free_expand_data();
				return (error_allocation(data));
			}
			if (has_quotes)
				data->exp_data->has_quotes = 1;
			return (1);
		}
		arg++;
	}
	return (0);
}

char	find_no_alnum(char *param)
{
	while (*param)
	{
		if (!ft_isalnum(*param))
			return (*param);
		param++;
	}
	return (0);
}

void	split_val(t_word *word, t_data *data)
{
	char	**splt;
	t_word	*tmp;
	t_word	*last;
	int	i;

	splt = ft_split(word->word, ' ');
	// if (!splt);
	i = -1;
	last = NULL;
	while (splt[++i])
	{
		tmp = ft_calloc(sizeof(t_word), sizeof(char));
		// if (!tmp)
		if (!data->exp_data->new)
			data->exp_data->new = tmp;
		tmp->word = ft_strdup(splt[i]);
		// if (!tmp->word)
		if (last)
			last->next = tmp;
		last = tmp;
		if (!splt[i + 1])
			tmp->next = data->exp_data->next_arg;
	}
	free(word->word);
	free(word);
	data->exp_data->prev_arg->next = data->exp_data->new;
}

int	has_spaces(char *s)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == ' ' || *s == '\t' || *s == '\v')
			return (1);
		s++;
	}
	return (0);
}

void	expand(t_data *data, t_word *word)
{
	char	*param;
	char	*last_part;
	t_env_node	*env_var;
	t_word	*new;

	param = ft_strchr(word->word, '$') + 1;
	last_part = ft_strchr(param, '"');
	last_part = ft_strchr(param, find_no_alnum(param));
	if (*last_part == '"')
		last_part = NULL;
	param = ft_substr(param, 0, ft_strlen(param) - ft_strlen(ft_strchr(param, find_no_alnum(param))));
	// if (!param)
	env_var = get_var(data->env, param);
	if (last_part)
	{
		new = ft_calloc(sizeof(t_word), sizeof(char));
		new->word = ft_strdup(last_part);
		word->next = new;
		new->next = data->exp_data->next_arg;
	}
	if (env_var)
	{
		free(word->word);
		word->word = ft_strdup(env_var->val);
	}
	if (env_var && data->exp_data->has_quotes && has_spaces(env_var->val))
		split_val(word, data);
}

