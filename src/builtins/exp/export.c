/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-06 22:18:54 by carlaugu          #+#    #+#             */
/*   Updated: 2025-03-06 22:18:54 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/builtins.h"

static	void sort_env(t_env_node *env_lst)
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

static void	print_export(t_env_node *env_lst)
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
static t_env_node	*get_last(t_env_node *env_lst)
{
	while (env_lst)
	{
		if (!env_lst->next)
			break;
		env_lst = env_lst->next;
	}
	return (env_lst);
}
void	add_var(t_env_node **env_lst, t_word *word_lst)
{
	t_env_node	*last;
	t_env_node	*tmp;

	last = get_last(*env_lst);
	tmp = ft_calloc(sizeof(t_env_node), sizeof(char));
	// if (!tmp)
		/*here: free everything or continue withou add var??*/
	tmp->var = word_lst->word;
	tmp->prev = last;
	if (last)
		last->next = tmp;
	if (!*env_lst)
		*env_lst = tmp;
}

int	update_var(t_env_node *tmp, char *arg, char **env_var, char **arg_var)
{
	if (ft_strcmp(tmp->var, arg) != 0)
	{
		free(tmp->var);
		tmp->var = arg;
	}
	free_strarray(env_var);
	free_strarray(arg_var);
	return (1);
}

int	exist_var(t_env_node *env_lst, char *argument)
{
	char	**env_var;
	char	**arg_var;

	if (!env_lst)
		return (0);
	arg_var = ft_split(argument, '=');
	while (env_lst)
	{
		env_var = ft_split(env_lst->var, '=');
		// if (!env_var)
		if (!ft_strcmp(arg_var[0], env_var[0]))
			return (update_var(env_lst, argument, env_var, arg_var));
		free_strarray(env_var);
		env_lst = env_lst->next;
	}
	free_strarray(arg_var);
	return (0);
}
void	export(t_word *word_lst, t_env_node **env_lst)
{
	if (!word_lst->next)
	{
		sort_env(*env_lst);
		print_export(*env_lst);
	}
	else
	{
		word_lst = word_lst->next;
		while (word_lst)
		{
			if(!exist_var(*env_lst, word_lst->word))
				add_var(env_lst, word_lst);
			word_lst = word_lst->next;
		}
	}
}
