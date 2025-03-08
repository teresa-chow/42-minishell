/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-08 15:16:37 by carlaugu          #+#    #+#             */
/*   Updated: 2025-03-08 15:16:37 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/utils.h"
#include "../../../include/builtins.h"

void sort_env(t_env_node *env_lst)
{
	int	check;
	char	*box;
	t_env_node	*tmp;

	if (!env_lst)
		return ;
	check = 1;
	while (check)
	{
		check = 0;
		tmp = env_lst;
		while (tmp && tmp->next)
		{
			if (ft_strcmp(tmp->var, tmp->next->var) > 0)
			{
				check = 1;
				box = tmp->var;
				tmp->var = tmp->next->var;
				tmp->next->var = box;
			}
			tmp = tmp->next;
		}
	}
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