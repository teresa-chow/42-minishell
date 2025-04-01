/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 18:14:28 by carlaugu          #+#    #+#             */
/*   Updated: 2025/04/01 14:17:14 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include "../../include/errors.h"
#include "../../include/special_cases.h"

int	get_exp_vars(char *arg, t_data *data)
{
	int	mid_len;
	char	*start;
	char	*end;

	mid_len = ft_strlen(arg) - (ft_strlen(data->exp->bfr) + ft_strlen(data->exp->aft));
	data->exp->mid = ft_calloc(mid_len + 1, sizeof(char));
	// if (!data->exp->mid)
	// 	return (free_exp());
	start = ft_strchr(arg, '$');
	end = ft_strchr(get_last_exp(arg), data->exp->no_alnum);
	ft_strlcpy(data->exp->mid, start, (end - start) + 1);
	return (0);
}

int	check_bfr_aft_mid(char *arg, t_data *data)
{
	char	*lst_exp;
	int	i;
	
	if (*arg != '$')
	{
		data->exp->bfr = ft_substr(arg, 0, ft_strlen(arg) - ft_strlen(ft_strchr(arg, '$')));
		// if (!data->exp->bfr)
		// 	return (free_exp());		
	}
	lst_exp = get_last_exp(arg);
	data->exp->no_alnum = find_no_alnum(lst_exp);
	if (data->exp->no_alnum)
	{
		i = ft_strlen(lst_exp) - ft_strlen(ft_strchr(lst_exp, data->exp->no_alnum));
		data->exp->aft = ft_substr(lst_exp, i, ft_strlen(ft_strchr(lst_exp, data->exp->no_alnum)));
		// if (!data->exp->aft)
		// 	return (free_exp());
	}
	if (get_exp_vars(arg, data) == -1)
		return(-1); // return (free_exp()); 
	return (0);
}

char	*get_name(char *s, t_data *data)
{
	char	c;
	char	*end;
	int	len;

	ft_bzero(&data->exp->buf, sizeof(data->exp->buf));
	ft_bzero(&data->exp->extra, sizeof(data->exp->extra));
	c = find_no_alnum(s);
	if (!c)
		return (s);
	if (c)
	{
		end = ft_strchr(s, c);
		len = ft_strlen(s) - ft_strlen(end);
		ft_strlcpy(data->exp->buf, s, len + 1);
		ft_strlcpy(data->exp->extra, end, ft_strlen(end) + 1);
	}
	return (data->exp->buf);
}

int	expand_vars(t_data *data)
{
	char	**arr;
	char	*tmp;
	t_env_node	*var;
	int	i;

	arr = ft_split(data->exp->mid, '$');
	// if (!data->exp->wrds)
	// 	return (free_exp())
	i = -1;
	tmp = NULL;
	free(data->exp->mid);
	data->exp->mid = NULL;
	while (arr[++i])
	{
		var = get_var(data->env, get_name(arr[i], data));
		if (var && var->val)
		{
			tmp = ft_strdup(var->val);
			// if (!tmp)
			// 	return (free_exp())
			data->exp->mid = ft_strjoin(data->exp->mid, tmp);
			// if (!data->exp->mid)
			// 	return (freE_exp())
			if (data->exp->extra[0])
			{
				data->exp->mid = ft_strjoin(data->exp->mid, data->exp->extra);
				// if (!data->exp->mid)
			// 	return (freE_exp())
			}
			if (tmp != data->exp->mid)
				free(tmp); 
		}
	}
	return (0);
}

// int	join_words(t_data *data, t_word *)
// {
// 	int	total_len;

// 	total_len = ft_strlen(data->exp->bfr) +  ft_strlen(data->exp->mid) +  ft_strlen(data->exp->aft);

// }

int	count_quotes(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] != '"')
			break;
	}
	return (i);
}
int	has_delimiter(char *arg)
{
	while (*arg)
	{
		if (is_delimiter(*arg))
		{
			if ((*arg == ' ' && (is_delimiter(*(arg + 1)))) || *arg != ' ')
				return (1);
		}
		arg++;
	}
	return (0);
}

int	handle_quotes(char *arg, t_data *data)
{
	int	n;

	(void)data;
	n = count_quotes(arg);
	if (n & 1)
		return (0);
	if (has_delimiter(data->exp->mid))
	{

	}
	return (0);
}

int	expand(t_data *data, t_word *word)
{
	t_env_node	*var;

	var = get_var(data->env, "ZZ");
	var->val = "Carlos Teixeira";



//////////////////////////////////////////////////////////////////
	data->exp = ft_calloc(sizeof(t_expand), sizeof(char));
	if (!data->exp)
		return (error_allocation(data));
	if (check_bfr_aft_mid(word->word, data) == -1)
		return (-1);
	if (expand_vars(data) == -1)
		return (-1);
	if (handle_quotes(word->word, data) == -1)
		return (-1);
	// if (join_words(data) == -1)
	// 	return (-1);
	return (0);
}
