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
#include "../../include/utils.h"

int	check_before_and_after(char *arg, t_data *data)
{
	char	*lst_exp;
	char	c;
	int	i;
	int	new_len;
	char	*start;
	char	*end;
	

	if (*arg != '$')
	{
		data->exp->bfr = ft_substr(arg, 0, ft_strlen(arg) - ft_strlen(ft_strchr(arg, '$')));
		// if (!data->exp->bfr)
		// 	return (free_exp());		
	}
	lst_exp = find_last_sign(arg);
	c = find_no_alnum(lst_exp);
	if (c)
	{
		i = 0;
		while (lst_exp[i] != c)
			i++;
		data->exp->aft = ft_substr(lst_exp, i, ft_strlen(lst_exp) - ft_strlen(ft_strchr(lst_exp, c)));
		// if (!data->exp->aft)
		// 	return (free_exp());
	}
	new_len = ft_strlen(arg) - (ft_strlen(data->exp->bfr) + ft_strlen(data->exp->aft));
	data->exp->new = ft_calloc(new_len + 1, sizeof(char));
	// if (!data->exp->new)
		// 	return (free_exp());
	start = ft_strchr(arg, '$');
	end = ft_strchr(lst_exp, c);
	i = 0;
	while (start != end)
		data->exp->new[i++] = *start++;
	return (0);
}

int	expand(t_data *data, t_word *word)
{
	data->exp = ft_calloc(sizeof(t_expand), sizeof(char));
	if (!data->exp)
		return (error_allocation(data));
	check_before_and_after(word->word, data);
	return (0);
}
