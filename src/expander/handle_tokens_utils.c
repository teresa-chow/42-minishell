/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_qts_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-10 23:02:03 by carlaugu          #+#    #+#             */
/*   Updated: 2025-04-10 23:02:03 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expand.h"

static int	exit_status_len(t_data *data);

/* This is an auxiliary function for get_var_len  and  get_expand_val*/
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

int	get_segment_len(char *bgn, char *end, t_data *data)
{
	int	len;
	int	new;

	if (!data->exp->to_exp)
		return (end - bgn);
	len = 0;
	new = 0;
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
			{
				new = expand_val_len(&bgn, data);
				if (new < 0)
					return (-1); 
				len = len + new;
			}
		}
		else
		{
			len++;
			bgn++;
		}
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

void	reset_small_part_flags(t_data *data)
{
	data->exp->in_sing = false;
	data->exp->in_dbl = false;
	data->exp->to_exp = false;
	data->exp->export_after_equal = false;
	data->exp->to_exp = false;
}

void	reset_big_part_flags(t_data *data)
{
	data->exp->has_dbl = false;
	data->exp->has_sing = false;
	data->exp->has_exp = false;
	data->exp->export_cmd = false;
	data->exp->to_split = false;
}
