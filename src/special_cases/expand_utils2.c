/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:38:40 by carlaugu          #+#    #+#             */
/*   Updated: 2025/04/03 15:50:15 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/errors.h"
#include "../../include/special_cases.h"
#include "../../include/utils.h"

/*extra functions to check_bfr_mid_aft*/
int	check_lst_exp(t_data *data, char *arg)
{
	char	*lst_exp;
	int	i;

	lst_exp = get_last_exp(arg) + 1;
	data->exp->no_alnum = find_extra(lst_exp);
	if (data->exp->no_alnum)
	{
		if (*lst_exp == '?' && *(lst_exp + 1) == '?')
			i = ft_strlen(lst_exp) - ft_strlen(ft_strchr(lst_exp + 2, data->exp->no_alnum));
		else
			i = ft_strlen(lst_exp) - ft_strlen(ft_strchr(lst_exp, data->exp->no_alnum));
		data->exp->aft = ft_substr(lst_exp, i, ft_strlen(ft_strchr(lst_exp, data->exp->no_alnum)) 
								- ft_strlen(ft_strchr(lst_exp, '"')));
		if (!data->exp->aft)
			return (-1);
	}
	return (0);
}



int	get_exp_vars(char *arg, t_data *data)
{
	int	mid_len;
	char	*start;
	char	*end;
	char	*last_exp;

	mid_len = ft_strlen(arg) - (ft_strlen(data->exp->bfr) 
		+ ft_strlen(data->exp->aft) + (count_begin_quotes(arg) + count_last_quotes(arg)));
	data->exp->mid = ft_calloc(mid_len + 1, sizeof(char));
	if (!data->exp->mid)
		return (-1);
	last_exp = get_last_exp(arg);
	if (data->exp->no_alnum == '$')
		last_exp++;
	start = get_valid_dollar(arg);
	if (*start == '$' && *(start + 1) == '?' && *(start + 2) == '?')
		end = ft_strchr(last_exp, data->exp->no_alnum) + 1;
	else
		end = ft_strchr(last_exp, data->exp->no_alnum);
	ft_strlcpy(data->exp->mid, start, (end - start) + 1);
	return (0);
}

char	first_char(char *arg)
{
	while (*arg)
	{
		if (*arg != '"')
			break;
		arg++;
	}
	return (*arg);
}
/*extra functions to expand_vars*/
int	get_var_val(t_data *data, int i, char **tmp)
{
	char	*name;
	t_env_node	*var;

	name = get_var_and_extra_chars(data->exp->arr[i], data);
	if (!name)
		return (-1);
	var = ft_getenv(data->env, name);
	if (var && var->val)
	{
		if (data->exp->mid)
		{
			*tmp = data->exp->mid;
			data->exp->mid = ft_strjoin(data->exp->mid, var->val);
			free(*tmp);
		}
		else
			data->exp->mid = ft_strdup(var->val);
		if (!data->exp->mid)
			return (-1);
	}
	return (0);
}

int	get_extra_chars(t_data *data, char **tmp)
{
	if (data->exp->extra)
	{
		if (data->exp->mid)
		{
			*tmp = data->exp->mid;
			data->exp->mid = ft_strjoin(data->exp->mid, data->exp->extra);
			free(*tmp);
		}
		else
			data->exp->mid = ft_strdup(data->exp->extra);
		if (!data->exp->mid)
			return (-1);
	}
	return (0);
}
