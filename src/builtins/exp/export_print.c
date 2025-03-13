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
			return (free_env_list(*copy, 1));
		tmp->var = ft_strdup(env->var);
		if (!tmp->var)
			return (free_env_list(*copy, 1));
		if (!*copy)
			*copy = tmp;
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
	t_env_node	*box;
	t_env_node	*tmp;
	t_env_node	*copy;

	if (!env_lst)
		return ;
	check = 1;
	copy = NULL;
	if (creat_copy(&copy, env_lst) == -1)
		return ;
	while (check)
	{
		check = 0;
		tmp = copy;
		while (tmp && tmp->next)
		{
			if (ft_strcmp(tmp->key, tmp->next->key) > 0)
			{
				check = 1;
				box = tmp;
				tmp = tmp->next;
			}
			tmp = tmp->next;
		}
	}
	print_export(copy);
	free_env_list(copy, 0);
}

static	int	print_var_name(char *s)
{
	while (*s)
	{
		ft_putchar_fd(*s, 1);
		if (*s == '=')
			return (1);
		s++;
	}
	return (0);
}
static	void	print_var_val(char *s)
{
	while (*s && *s != '=')
		s++;
	if (*s == '=')
		s++;
	ft_putchar_fd('"', 1);
	while (*s)
		ft_putchar_fd(*s++, 1);
	ft_putchar_fd('"', 1);
}

void	print_export(t_env_node *env_lst)
{
	while (env_lst)
	{
		ft_putstr_fd("declare -x ", 1);
		if (print_var_name(env_lst->var))
			print_var_val(env_lst->var);
		write(1, "\n", 1);
		env_lst = env_lst->next;
	}
}