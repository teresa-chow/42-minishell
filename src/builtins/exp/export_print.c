/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 15:16:37 by carlaugu          #+#    #+#             */
/*   Updated: 2025/03/12 12:20:43 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/utils.h"
#include "../../../include/builtins.h"

int	creat_copy(t_env_node **copy, t_env_node *env)
{
	t_env_node	*tmp;
	t_env_node	*last;

	last = NULL;
	while (env)
	{
		tmp = ft_calloc(sizeof(t_env_node), sizeof(char));
		if (!tmp)
			return (free_env_list(copy, 1));
		if (!*copy)
			*copy = tmp;
		tmp->key = ft_strdup(env->key);
		tmp->val = ft_strdup(env->val);
		if (!tmp->key || (!tmp->val && env->val))
			return(free_env_list(copy, 1));
		tmp->prev = last;
		if (tmp->prev)
			tmp->prev->next = tmp;
		last = tmp;
		env = env->next;	
	}
	return (0);
}

void sort_env(t_env_node *env_lst)
{
	int	check;
	char	*box;
	t_env_node	*tmp;
	t_env_node	*copy;

	if (!env_lst)
		return ;
	copy = NULL;
	if (creat_copy(&copy, env_lst) == -1)
		return ;
	check = 1;
	while (check)
	{
		check = 0;
		tmp = copy;
		while (tmp && tmp->next)
		{
			if (ft_strcmp(tmp->key, tmp->next->key) > 0)
			{
				check = 1;
				box = tmp->next->key;
				tmp->next->key = tmp->key;
				tmp->key = box;
				box = tmp->next->val;
				tmp->next->val = tmp->val;
				tmp->val = box;
			}
			else
				tmp = tmp->next;
		}
	}
	print_export(copy);
	free_env_list(&copy, 0);
}

static	void	print_var_val(char *s)
{
	ft_putchar_fd('"', 1);
	ft_putstr_fd(s, 1);
	ft_putchar_fd('"', 1);
}

void	print_export(t_env_node *env_lst)
{
	while (env_lst)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env_lst->key, 1);
		if (env_lst->val)
		{
			write (1, "=", 1);
			print_var_val(env_lst->val);
		}
		write(1, "\n", 1);
		env_lst = env_lst->next;
	}
}