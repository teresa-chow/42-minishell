/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 21:13:12 by carlaugu          #+#    #+#             */
/*   Updated: 2025/03/11 13:39:43 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/builtins.h"
#include "../../../include/utils.h"
#include "../../../include/errors.h"

char	find_sep(char *s)
{
	char	*tmp;

	tmp = s;
	while (*tmp)
	{
		if (*tmp == '+' && *(tmp + 1) == '=')
			return ('+');
		// else if (*tmp == '+' && *(tmp + 1) != '=')
		// {
		// 	wrong_export_sintax(s);
		// 	return (0);                
		// }                               // -----> se the comment in 130 line about sintax
		tmp++;
	}
	return ('=');
}

int	update_var(t_env_node *env, t_ipt_inf *arg_inf)
{
	char	*new;
	char	*new_val;

	if (arg_inf->sep == '+' && ft_strchr(env->var, '='))
	{
		new_val = ft_strdup(ft_strchr(arg_inf->val, '=') + 1);
		if (!new_val)
			return (error_allocation());
		free(arg_inf->val);
		arg_inf->val = new_val;
		new = ft_strjoin(env->var, arg_inf->val);
		if (!new)
			return (error_allocation());
		free(env->var);
		env->var = new;
	}
	else
	{
		new = ft_strjoin(arg_inf->key, arg_inf->val);
		if (!new)
			return (error_allocation());
		free(env->var);
		env->var = new;
	}
	return (1);
}

int	exist_var(t_env_node *env, t_ipt_inf *inf_arg)
{
	char	*key;
	
	key = NULL;
	while (env)
	{
		key = ft_substr(env->var, 0, ft_strlen(env->var) - ft_strlen(ft_strchr(env->var, '=')));
		if (!key)
			return (error_allocation());
		if (!ft_strcmp(key, inf_arg->key))
		{
			free(key);
			if (*inf_arg->val)
				return (update_var(env, inf_arg));
			else
				return (1);
		}
		free(key);
		env = env->next;
	}
	return (0);
}
t_env_node	*get_last(t_env_node *env_lst)
{
	while (env_lst)
	{
		if (!env_lst->next)
			break;
		env_lst = env_lst->next;
	}
	return (env_lst);
}

static void	change_ptrs(t_env_node *last, t_env_node *tmp, t_env_node **env)
{
	if (last)
	{
		last->next = tmp;
		tmp->prev = last;
	}
	if (!*env)
		*env = tmp;
}

int	add_var(t_env_node **env, t_ipt_inf *inf_arg)
{
	int	check;
	t_env_node	*last;
	t_env_node	*tmp;

	check = exist_var(*env, inf_arg);
	if (check == -1 || check == 1)
		return (check);
	else
	{
		last = get_last(*env);
		tmp = ft_calloc(sizeof(t_env_node), sizeof(char));
		if (!tmp)
			return (-1);
		tmp->var = ft_strjoin(inf_arg->key, inf_arg->val);
		if (!tmp->var)
		{
			free(tmp);
			return (-1);
		}
		change_ptrs(last, tmp, env);
	}
	return (0); 
}
int	set_inf(char *word, t_ipt_inf *inf_arg)
{
	inf_arg->sep = find_sep(word);
	inf_arg->key = ft_substr(word, 0, ft_strlen(word) - ft_strlen(ft_strchr(word, inf_arg->sep)));
	if (!inf_arg->key)
		return (error_allocation());
	inf_arg->val_strt = ft_strlen(word) - ft_strlen(ft_strchr(word, '='));
	inf_arg->val = ft_substr(word, inf_arg->val_strt, ft_strlen(ft_strchr(word, '=')));
	if (!inf_arg->val)
	{
		free(inf_arg->key);
		return (error_allocation());
	}
	return (0);
}

void	reset_inf(t_ipt_inf *inf)
{
	free(inf->key);
	free(inf->val);
	inf->sep = 0;
	inf->val_strt = 0;
}
/// this builtin can't have (export ARG++23), the sintax is not correct, so we have
// to handle with this, maybe in expand part??
// --> same to (export ZA,ZB)

void	export(t_word *word_lst, t_env_node **env_lst)
{
	t_ipt_inf	inf_arg;

	if (!word_lst->next)
	{
		sort_env(*env_lst);
		print_export(*env_lst);
	}
	else
	{
		ft_bzero(&inf_arg, sizeof(t_ipt_inf));
		word_lst = word_lst->next;
		while (word_lst)
		{
			if (set_inf(word_lst->word, &inf_arg) == -1)
				return ;
			if (add_var(env_lst, &inf_arg) == -1)
				return ;
			reset_inf(&inf_arg);
			word_lst = word_lst->next;
		}
	}
}
