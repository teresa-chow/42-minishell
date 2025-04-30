/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tokens_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 23:02:03 by carlaugu          #+#    #+#             */
/*   Updated: 2025/04/30 17:24:52 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expand.h"

static int	exit_status_len(t_data *data);
static int	get_expand_len(t_data *data, char **bgn, int *len);

int	get_segment_len(char *bgn, char *end, t_data *data)
{
	int	len;

	if (!data->exp->to_exp)
		return (end - bgn);
	len = 0;
	while (bgn != end)
	{
		if (*bgn == '$' && is_valid_dollar(bgn))
		{
			if (get_expand_len(data, &bgn, &len) == -1)
				return (-1);
		}
		else
		{
			len++;
			bgn++;
		}
	}
	return (len);
}

static int	get_expand_len(t_data *data, char **bgn, int *len)
{
	int	new;

	new = 0;
	if (*(*bgn + 1) == '?')
	{
		*len += exit_status_len(data);
		*bgn += 2;
	}
	else
	{
		new = expand_val_len(bgn, data);
		if (new < 0)
			return (-1); 
		*len = *len + new;
	}
	return (0);
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

void	reset_small_part_flags(t_data *data)
{
	data->exp->in_sing = false;
	data->exp->in_dbl = false;
	data->exp->to_exp = false;
	data->exp->export_has_equal = false;
	data->exp->to_exp = false;
	data->exp->to_split = false;
}

void	reset_big_part_flags(t_data *data)
{
	data->exp->has_dbl = false;
	data->exp->has_sing = false;
	data->exp->has_exp = false;
	data->exp->export_cmd = false;
	data->exp->to_split = false;
}
