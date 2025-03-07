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

char	find_sep(char *word)
{
	while (*word)
	{
		if (*word == '+' && *(word + 1) == '=')
			return ('+');
		word++;
	}
	return ('=');
}
int	exist_var(t_env_node *env_lst, char *arg ,char sep)
{
	char	**env_var;
	char	**arg_var;

	arg_var = ft_split(arg, sep);
	while (env_lst)
	{
		env_var = ft_split(env_lst->var, '=');
		if (!ft_strcmp(env_var[0], arg_var[0]))
		{
			///if existe update var
			return (1);
		}
		free_strarray(env_var);
		env_lst = env_lst->next;
	}
	free_strarray(arg_var);
	return (0);
}

void	add_var(t_env_node **env_lst, char *arg, char sep)
{
	t_env_node	*last;
	t_env_node	*tmp;
	char	**var;

	last = get_last(*env_lst);
	tmp = ft_calloc((sizeof(t_env_node)), sizeof(char)); ///if faill malloc....
	if (sep == '+')
	{
		var = ft_split(arg, sep);
		tmp->var = ft_strjoin(var[0], var[1]);
		free_strarray(var);
	}
	else
		tmp->var = ft_strdup(arg);
	if (last)
	{
		last->next = tmp;
		tmp->prev = last;
	}
	if (!*env_lst)
		*env_lst = tmp;
	
}

void	export(t_word *word_lst, t_env_node **env_lst)
{
	char	sep;

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
			sep = find_sep(word_lst->word);
			if(exist_var(*env_lst, word_lst->word, sep))
			{

			}
			else
				add_var(env_lst, word_lst->word, sep);
			word_lst = word_lst->next;
		}
	}
}
