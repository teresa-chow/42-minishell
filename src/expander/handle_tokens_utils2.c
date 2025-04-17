/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tokens_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:44:44 by carlaugu          #+#    #+#             */
/*   Updated: 2025/04/17 11:04:15 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expand.h"

static int	get_len_and_end(t_data *data, int *len, char **end, char **ptr);
static	int	updt_new_or_tword(t_data *data, char *srt, char *end, int len);

void	tmp_str_change(char **ptr, char **no_alnum, char *box, bool end)
{
	if (!end)
	{
		*no_alnum = find_non_alnum(*ptr);
		*box = **no_alnum;
		**no_alnum = 0;
	}
	if (end)
	{
		**no_alnum = *box;
		*ptr = *no_alnum;
	}
}

/* 
`ptr` advances the outer pointer `cpy` from `process_token`
until the end of the segment (`end`).
*/
int	exp_join_segment(t_data *data, char **ptr, int len, char *end)
{
	char	*start;
	char	*tmp;
	int	i;

	i = get_len_and_end(data, &len, &end, ptr);
	if (i == -1 || i == 1)
		return (i);
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
	if (updt_new_or_tword(data, start, tmp, len) == -1)
		return (-1);
	return (0);
}

static	int	updt_new_or_tword(t_data *data, char *srt, char *end, int len)
{
	int	i;

	i = 0;
	if (data->exp->to_split || data->exp->export_exp_bfr_equal)
		i = rebuild_tword(data, data->word, srt);
	else
		i = build_new(data, srt, end, len);
	free(srt);
	return (i);
}

static int	get_len_and_end(t_data *data, int *len, char **end, char **ptr)
{
	if (!data->exp->in_dbl)
	{
		*end = find_next_quote_and_parse(*ptr, data);
		*len = get_segment_len(*ptr, *end, data);
	}
	if (*len < 0)
		return (-1);
	else if (!*len)
	{
		*ptr = *end;
		return (1);
	}
	return (0);
}

int	handle_quotes(char **ptr, t_data *data)
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
	if (len < 0)
		return (-1);
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
