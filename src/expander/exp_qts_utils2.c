/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_qts_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-07 15:35:18 by carlaugu          #+#    #+#             */
/*   Updated: 2025-04-07 15:35:18 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expand.h"

static int	exit_status_len(t_data *data);
static int	var_val_len(char *s, t_data *data, char **bgn);
static int	len_splited_words(t_data *data, char *val);

void	reset_checkers(t_data *data)
{
	data->exp->has_dbl = false;
	data->exp->has_exp = false;
	data->exp->has_sing = false;
	data->exp->in_dbl = false;
	data->exp->in_sing = false;
	data->exp->to_exp = false;
}

/* These function get the length of normal chars with expansions */
int	get_len(char *bgn, char *end, t_data *data)
{
	int	len;

	if (!data->exp->to_exp)
		return (end - bgn);
	len = 0;
	while (bgn != end)
	{
		if (*bgn == '$' && is_valid_dollar(bgn))
		{
			if (*(bgn + 1) == '?')
			{
				len += exit_status_len(data);
				bgn += 2;
			}
			else
				len += var_val_len(bgn + 1, data, &bgn);
		}
		else
		{
			len++;
			bgn++;
		}
	}
	data->exp->words = 0;
	return (len);
}

static int	var_val_len(char *s, t_data *data, char **bgn)
{
	t_env_node	*var;
	char	*non_alnum;
	char	box;
	int	len;

	len = 0;
	non_alnum = find_non_alnum(s);
	box = *non_alnum;
	*non_alnum = 0;
	var = ft_getenv(data->env, s);
	if (var)
	{
		if (has_delimiter(var->val) && !data->exp->in_dbl)
		{
			len = len_splited_words(data, var->val);
			if (len == -1)
				return (-1);
			free_strarray(data->exp->words);
		}
		else
			len = ft_strlen(var->val);
	}
	*non_alnum = box;
	*bgn = non_alnum;
	return (len);
}

static int	len_splited_words(t_data *data, char *val)
{
	int	i;
	int	len;

	len = 0;
	data->exp->words = get_words(val);
	if (!data->exp->words)
		return (-1);
	i = -1;
	while (data->exp->words[++i])
	{
		len += ft_strlen(data->exp->words[i]);
		if (data->exp->words[i + 1])
			len++;
	}
	return (len);
}

static int	exit_status_len(t_data *data)
{
	int	i;
	int	n;

	i = 0;
	n = data->exit_status;
	if (!data->exit_status)
		return (1);
	while (n)
	{
		i++;
		n /= 10;
	}
	return (i);
}
