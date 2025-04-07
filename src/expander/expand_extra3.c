/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_extra3.c.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-05 10:49:42 by carlaugu          #+#    #+#             */
/*   Updated: 2025-04-05 10:49:42 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expand.h"

static int	get_invalid_part(char *tmp, t_data *data);

/*extra functions to expand_vars*/
int	set_mid(t_data *data, char **tmp)
{
	int	i;

	i = -1;
	while (data->exp->arr[++i])
	{
		if (data->exp->arr[i][0] == '?')
		{
			if (expand_dollar(data, tmp, i) == -1)
				return (-1);
		}
		else if (get_var_val(data, i, tmp) == -1)
			return(-1);
		if (get_extra_chars(data, tmp) == -1)
			return(-1);
		if (data->exp->invalid_str && i == data->exp->invalid_pos)
		{
			*tmp = data->exp->mid;
			data->exp->mid = ft_strjoin(data->exp->mid, data->exp->invalid_str);
			if (!data->exp->mid)
				return (-1);
			free_many(tmp, &data->exp->invalid_str, NULL);
		}
	}
	return (0);
}

int	is_valid_mid(t_data *data)
{
	char *tmp;
	int	i;

	if (!data->exp->mid)
		return (0);
	i = -1;
	tmp = data->exp->mid;
	while (*tmp)
	{
		if (*tmp == '$' && *(tmp + 1) != '$')
			i++;
		else if ((*tmp == '$' && *(tmp + 1) == '$'))
		{
			data->exp->invalid_pos = i;
			if (get_invalid_part(tmp, data) == -1)
				return (-1);
			else
				break;
		}
		tmp++;
	}
	return (0);
}

static int	get_invalid_part(char *tmp, t_data *data)
{
	int	i;
	char	*start;

	i = 0;
	start = tmp;
	while (*tmp == '$' && *(tmp + 1) == '$')
	{
		i++;
		tmp++;
	}
	data->exp->invalid_str = ft_calloc(i + 1, sizeof(char));
	if (!data->exp->invalid_str)
		return (-1);
	add_chars(start, tmp, data->exp->invalid_str);
	return (0);
}

// int	expand_til()
// {}