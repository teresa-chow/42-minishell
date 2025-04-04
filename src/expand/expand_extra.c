/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_extra_funcs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-04 14:22:41 by carlaugu          #+#    #+#             */
/*   Updated: 2025-04-04 14:22:41 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expand.h"

int	find_expand(t_word *word, t_data *data)
{
	char	*tmp;

	while (word)
	{
		tmp =word->word;
		while (*tmp)
		{
			if (*tmp == '$' && (ft_isalnum(*(tmp + 1)) || *(tmp + 1) == '?'))
			{
				if (expand(data, word) == -1)
					return (-1);
				break;
			}
			tmp++;
		}
		free_exp(data, word, 0);
		word = word->next;
	}
	return (0);
}

/*extra functions to get_before_mid_aft*/
int	get_before(char *arg, t_data *data)
{
	char	*end;
	int	i;

	end = get_valid_dollar(arg);
	i = count_no_quotes(arg, end);
	if (!i)
		return (0);
	data->exp->bfr = ft_calloc(i + 1, sizeof(char));
	add_no_quotes(data->exp->bfr, arg, end);
	return (0);
}

int	get_after(t_data *data, char *arg)
{
	char	*lst_exp;
	char	*start;
	char	*end;

	start = 0;
	end = 0;
	lst_exp = get_last_exp(arg) + 1;
	if (*lst_exp == '?' && *(lst_exp + 1) == '?')
		start = lst_exp + 1;
	else
		start = ft_strchr(lst_exp, find_extra_var_name(lst_exp));
	if (!*start)
		return (0);
	data->exp->no_alnum = *start;
	end = ft_strchr(start, 0);
	data->exp->aft = ft_calloc(count_no_quotes(start, end) + 1, sizeof(char));
	if (!data->exp->aft)
		return (-1);
	add_no_quotes(data->exp->aft, start, end);
	return (0);
}

int	get_mid(char *arg, t_data *data)
{
	char	*start;
	char	*end;
	char	*last;
	int	len;

	start = get_valid_dollar(arg);
	last = get_last_exp(arg);
	// if (data->exp->no_alnum == '$')
	// 	last++;
	end = ft_strchr(last + 1, find_extra_var_name(last + 1));
	if (*end == '?' && *(end + 1) == '?')
		end = end + 1;
	len = ft_strlen(data->exp->bfr) + ft_strlen(data->exp->aft) + count_begin_quotes(arg) 
						+ count_end_quotes(arg);
	len = ft_strlen(arg) - len;
	data->exp->mid = ft_calloc(len + 1, sizeof(char));
	if (!data->exp->mid)
		return (-1);
	add_no_quotes(data->exp->mid, start, end);
	return (0);
}

/* Used to handle_quotes */
int	join_with_space(t_data *data, char **to_free)
{
	int	i;

	i = 0;
	while (data->exp->words[++i])
	{
		data->exp->mid = join_three(data->exp->mid, " ", data->exp->words[i]);
		if (!data->exp->mid)
			return (-1);
		free(*to_free);
		*to_free = data->exp->mid;
	}
	return (0);
}