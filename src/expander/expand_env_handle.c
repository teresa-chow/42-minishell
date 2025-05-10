/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_handle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:42:51 by carlaugu          #+#    #+#             */
/*   Updated: 2025/04/30 23:46:23 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expand.h"

static int	split_words_len(t_data *data, char *val);
static int	find_and_get_expand_value(t_data *data, char **ptr, char **tmp);

int	get_expand_val(t_data *data, char **ptr, char **tmp)
{
	char	*end_val;
	char	*exit_val;
	char	*no_alnum;
	char	box;

	(*ptr)++;
	tmp_str_change(ptr, &no_alnum, &box, false);
	if (**ptr == '?')
	{
		exit_val = ft_itoa(data->exit_status);
		if (!exit_val)
			return (-1);
		end_val = ft_strchr(exit_val, 0);
		add_chars(exit_val, end_val, *tmp);
		*tmp += ft_strlen(exit_val);
		free(exit_val);
	}
	else
		find_and_get_expand_value(data, ptr, tmp);
	tmp_str_change(ptr, &no_alnum, &box, true);
	return (0);
}

static int	find_and_get_expand_value(t_data *data, char **ptr, char **tmp)
{
	t_env_node	*var;
	char		*end_val;

	var = ft_getenv(data->env, *ptr);
	if (var && var->val && **ptr != '?')
	{
		if (has_delimiter(var->val) && !data->exp->in_dbl
			&& !data->exp->export_has_equal)
		{
			data->exp->to_split = true;
			if (join_split_words(data, tmp, var->val) == -1)
				return (-1);
		}
		else
		{
			end_val = ft_strchr(var->val, 0);
			add_chars(var->val, end_val, *tmp);
			*tmp += ft_strlen(var->val);
		}
		if (var->env_literal)
			data->exp->literal = true;
	}
	return (0);
}

int	expand_val_len(char **bgn, t_data *data)
{
	t_env_node	*var;
	char		*no_alnum;
	char		box;
	int			len;

	(*bgn)++;
	len = 0;
	tmp_str_change(bgn, &no_alnum, &box, false);
	var = ft_getenv(data->env, *bgn);
	if (var && var->val)
	{
		if (has_delimiter(var->val) && !data->exp->in_dbl
			&& !data->exp->export_has_equal)
		{
			len = split_words_len(data, var->val);
			if (len == -1)
				return (-1);
		}
		else
			len = ft_strlen(var->val);
	}
	tmp_str_change(bgn, &no_alnum, &box, true);
	return (len);
}

static int	split_words_len(t_data *data, char *val)
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
	free_strarray(data->exp->words);
	data->exp->words = 0;
	return (len);
}
