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

static int	exp_join_segment(t_data *data, char **ptr, int len, char *end);
static int	first_check(t_data *data, int *len, char **end, char **ptr);
static int	handle_quotes(char **ptr, t_data *data);
static int	process_token(t_word *word, t_data *data);

int	handle_tokens(t_word *word, t_data *data)
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
			if (process_token(word, data) == -1)
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

static int	process_token(t_word *word, t_data *data)
{
	char	*ptr;
	int	i;

	ptr = word->word;
	if (data->exp->export_cmd && *ptr == '$')
			data->exp->to_split = true;
	while (*ptr)
	{
		if (*ptr == '$' && (*(ptr + 1) == '\'' || *(ptr + 1) == '"'))
			ptr++;
		if (*ptr == '\'' || *ptr == '"')
			i = handle_quotes(&ptr, data);
		else
			i = exp_join_segment(data, &ptr, 0, NULL);
		if (i == -1)
			return (-1);
		reset_small_part_flags(data);
	}
	free(word->word);
	word->word = data->exp->new;
	data->exp->new = NULL;
	return (0);
}

static int	exp_join_segment(t_data *data, char **ptr, int len, char *end)
{
	char	*start;
	char	*tmp;

	if (first_check(data, &len, &end, ptr) == 2)
		return (0);
	tmp = ft_calloc(len + 1, sizeof(char));
	if (!tmp)
		return (-1);
	start = tmp;
	while (*ptr != end)
	{
		if (**ptr == '$' && is_valid_dollar(*ptr))
		{
			if (get_expand_val(data, ptr, &tmp) == -1)
				return (-1);
		}
		else
			*tmp++ = *(*ptr)++;
	}
	build_new(data, start, tmp, len);
	free(start);
	return (0);
}

static int	first_check(t_data *data, int *len, char **end, char **ptr)
{
	if (!data->exp->in_dbl)
	{
		*end = find_next_quote_and_parse(*ptr, data);
		*len = get_segment_len(*ptr, *end, data);
	}
	if (!*len)
	{
		*ptr = *end;
		return (2);
	}
	return (0);
}

static int	handle_quotes(char **ptr, t_data *data)
{
	int	i;
	int	len;
	char	*end;

	if (**ptr == '\'')
		data->exp->in_sing = true;
	else if (**ptr == '"')
		data->exp->in_dbl = true;
	(*ptr)++;
	end = find_next_quote_and_parse(*ptr, data);
	len = get_segment_len(*ptr, end, data);
	if (!data->exp->to_exp)
		i = build_new(data, *ptr, end, len);
	else
		i = exp_join_segment(data, ptr, len, end);
	if (i == -1)
		return (-1);
	if (*end)
		*ptr = end + 1;
	else
		*ptr = end;
	return (0);
}

