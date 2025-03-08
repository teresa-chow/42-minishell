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
#include "../../../include/utils.h"

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
		else if (*word == '+' && *(word + 1) != '=')
			return (0);
		word++;
	}
	return ('=');
}
static int	has_content(char *str)
{
	if ((*str == '=') && (*(str + 1) != '\0'))
		return (1);
	return (0);
}

static int	has_equal(char *s)
{
	while (*s)
	{
		if (*s == '=')
			return (1);
		s++;
	}
	return (0);
}

int	update_var(t_env_node *env_lst, char *arg, char **env_v, char **arg_v, char sep)
{
	char	**var_arg;
	char	*tmp;
	char	*tmp1;

	if (sep == '+' && has_content(arg_v[1]))
	{
		var_arg = ft_split(arg, '=');
		if (!has_equal(env_lst->var))
		{
			tmp = ft_strjoin(env_v[0], "=");
			tmp1 = ft_strjoin(tmp, env_v[1]);
			if (tmp != tmp1)
				free(tmp);
			tmp = ft_strjoin(tmp1, var_arg[1]);
			free(tmp1);
			free(env_lst->var);
			env_lst->var = tmp;
		}
		else
		{
			tmp = ft_strjoin(env_lst->var, var_arg[1]);
			free(env_lst->var);
			env_lst->var = tmp;
		}

		free_strarray(var_arg);
	}
	else if (sep == '=')
	{
		free(env_lst->var);
		tmp = ft_strjoin(env_v[0], "=");
		env_lst->var = ft_strjoin(tmp, arg_v[1]);
		if (env_lst->var != tmp)
			free(tmp);
	}
	free_strarray(env_v);
	free_strarray(arg_v);
	return (1);
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
			return (update_var(env_lst, arg, env_var, arg_var, sep));
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
	char	*tmp;
	char	*tmp1;

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
			if (sep != '+' && sep != '=')
			{
				tmp = ft_strjoin("minishell: export: `", word_lst->word);
				tmp1 = ft_strjoin(tmp, "': not a valid identifier");
				free(tmp);
				ft_putendl_fd(tmp1, 2);
				free(tmp1);
				return ;
			}
			if(exist_var(*env_lst, word_lst->word, sep))
			{

			}
			else
				add_var(env_lst, word_lst->word, sep);
			word_lst = word_lst->next;
		}
	}
}
