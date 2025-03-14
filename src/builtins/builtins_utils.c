/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-14 21:20:25 by carlaugu          #+#    #+#             */
/*   Updated: 2025-03-14 21:20:25 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include "../../include/errors.h"

t_env_node	*last_node(t_env_node *env_lst)
{
	while (env_lst)
	{
		if (!env_lst->next)
			break;
		env_lst = env_lst->next;
	}
	return (env_lst);
}

char	find_sep(char *s)
{
	char	*tmp;

	tmp = s;
	while (*tmp)
	{
		if (*tmp == '+' && *(tmp + 1) == '=')
			return ('+');
		// else if (*tmp == '+' && *(tmp + 1) != '=') OR "-="
		// {
		// 	wrong_export_sintax(s);
		// 	return (0);                
		// }                          // -----> se the comment in 130 line about sintax
		else if (*tmp == '=')
			return ('=');
		tmp++;
	}
	return (0);
}

int	set_inf(char *word, t_ipt_inf *inf_arg)
{
	int	len_wrd;
	char	*equal;

	equal = NULL;
	len_wrd = ft_strlen(word);
	inf_arg->sep = find_sep(word);
	inf_arg->key = ft_substr(word, 0, len_wrd - ft_strlen(ft_strchr(word, inf_arg->sep)));
	if (!inf_arg->key)
	return (-1);
	if (inf_arg->sep)
	{
		equal = ft_strchr(word, '=');
		inf_arg->val_strt = len_wrd - ft_strlen(equal + 1);
		inf_arg->val = ft_substr(word, inf_arg->val_strt, ft_strlen(equal + 1));
		if (!inf_arg->val)
		{
			free(inf_arg->key);
			return (error_allocation());
		}
	}
	return (0);
}
