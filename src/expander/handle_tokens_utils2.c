/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tokens_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-14 14:44:44 by carlaugu          #+#    #+#             */
/*   Updated: 2025-04-14 14:44:44 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expand.h"

static int	first_check(t_data *data, int *len, char **end, char **ptr);

int	exp_join_segment(t_data *data, char **ptr, int len, char *end)
{
	char	*start;
	char	*tmp;
	int	i;

	i = first_check(data, &len, &end, ptr);
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
