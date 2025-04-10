/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_qts_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:25:40 by carlaugu          #+#    #+#             */
/*   Updated: 2025/04/10 17:54:09 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expand.h"

static int	handle_arg(t_word *word, t_data *data);
int	handle_exp_qts(char **ptr, t_data *data);
int	rebuild_tword(t_data *data, t_word **word);
void	reset_small_part_flags(t_data *data);
static void	find_and_get_var_value(t_data *data, char **ptr, char **tmp);

int	analyze_args(t_word *word, t_data *data)
{
	data->exp = ft_calloc(sizeof(t_expand), sizeof(char));
	if (!data->exp)
		return (error_allocation(data));
	while (word)
	{
		if (analyze_token_context(&word, data) == -1)
			return(free_exp(data, word, 1));
		if (data->exp->has_dbl || data->exp->has_sing || data->exp->has_exp)
		{
			if (handle_arg(word, data) == -1)
				return(free_exp(data, word, 1));
			if (data->exp->to_split)
			{
				if (rebuild_tword(data, &word) == -1)
					return (free_exp(data, word, 1));
			}
			reset_big_part_flags(data);
		}
		word = word->next;
	}
	return (0);
}

static int	handle_arg(t_word *word, t_data *data)
{
	char	*ptr;
	int	i;

	ptr = word->word;
	while (*ptr)
	{
		if (*ptr == '\'' || *ptr == '"')
			i = handle_exp_qts(&ptr, data);
		else
			i = join_normal_and_expansion(data, &ptr, 0, NULL);
		if (i == -1)
			return (-1);
		reset_small_part_flags(data);
	}
	free(word->word);
	word->word = data->exp->new;
	data->exp->new = NULL;
	return (0);
}

int	rebuild_tword(t_data *data, t_word **word)
{
	t_word	*old_next;
	t_word	*tmp;
	t_word	*last;
	int	i;

	old_next = (*word)->next;
	data->exp->words = get_words((*word)->word);
	if (!data->exp->words)
		return (-1);
	free((*word)->word);
	(*word)->word = data->exp->words[0];
	i = 0;
	last = *word;
	while (data->exp->words[++i])
	{
		tmp = ft_calloc(sizeof(t_word), sizeof(char));
		if (!tmp)
			return (-1);
		last->next = tmp;
		tmp->word = data->exp->words[i];
		last = tmp;
	}
	last->next = old_next;
	*word = last;
	return (0);
}

void	reset_small_part_flags(t_data *data)
{
	data->exp->in_sing = false;
	data->exp->in_dbl = false;
	data->exp->to_exp = false;
	data->exp->export_after_equal = false;
	data->exp->to_exp = false;
}

int	get_var_val(t_data *data, char **ptr, char **tmp)
{
	char	*end_val;
	char	*exit_val;
	char	*inval;
	char	box;

	end_val = NULL;
	exit_val = NULL;
	inval = NULL;
	box = 0;
	(*ptr)++;
	temp_string_change(ptr, &inval, &box, false);
	if (**ptr == '?')
	{
		exit_val = ft_itoa(data->exit_status);
		if (!exit_val)
			return (-1);
		end_val = ft_strchr(exit_val, 0);
		add_chars(exit_val, end_val, *tmp);
		*tmp += ft_strlen(exit_val);
	}
	else
		find_and_get_var_value(data, ptr, tmp);
	temp_string_change(ptr, &inval, &box, true);
	return (0);
}
/* This is an auxiliary function for get_var_len */
static void	find_and_get_var_value(t_data *data, char **ptr, char **tmp)
{
	t_env_node	*var;
	char	*end_val;

	var = ft_getenv(data->env, *ptr);
	if (var && var->val && **ptr != '?')
	{
		if (has_delimiter(var->val) && !data->exp->in_dbl && !data->exp->export_after_equal)
		{
			data->exp->to_split = true;
			join_splited_words(data, tmp);
		}
		else
		{
			end_val = ft_strchr(var->val, 0);
			add_chars(var->val, end_val, *tmp);
			*tmp += ft_strlen(var->val);
		}
	}
}

int	join_normal_and_expansion(t_data *data, char **ptr, int len, char *end)
{
	char	*start;
	char	*tmp;

	if (!data->exp->in_dbl)
	{
		end = find_next_quote_and_parse(*ptr, data);
		len = get_total_len(*ptr, end, data);
	}
	if (!len)
	{
		*ptr = end;
		return (0);
	}
	tmp = ft_calloc(len + 1, sizeof(char));
	if (!tmp)
		return (-1);
	start = tmp;
	while (*ptr != end)
	{
		if (**ptr == '$' && is_valid_dollar(*ptr))
		{
			if (get_var_val(data, ptr, &tmp) == -1)
				return (-1);
		}
		else
			*tmp++ = *(*ptr)++;
	}
	build_new(data, start, tmp, len);
	free(start);
	return (0);
}

int	handle_exp_qts(char **ptr, t_data *data)
{
	int	i;
	int	len;
	char	*end;

	if (**ptr == '\'')
		data->exp->in_sing = true;
	else if (**ptr == '"')
		data->exp->in_dbl = true;
	end = find_next_quote_and_parse(*ptr + 1, data);
	len = get_total_len(*ptr + 1, end,data);
	if (!data->exp->to_exp)
		i = build_new(data, *ptr + 1, end, len);
	else
	{
		(*ptr)++;
		i = join_normal_and_expansion(data, ptr, len, end);
	}
	if (i == -1)
		return (-1);
	if (*end)
		*ptr = end + 1;
	else
		*ptr = end;
	return (0);
}

