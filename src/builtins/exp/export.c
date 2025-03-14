/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 21:13:12 by carlaugu          #+#    #+#             */
/*   Updated: 2025/03/12 12:07:03 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/builtins.h"
#include "../../../include/utils.h"
#include "../../../include/errors.h"

void	reset_inf(t_ipt_inf *inf)
{
	free(inf->key);
	if (inf->val)
		free(inf->val);
	inf->sep = 0;
	inf->val_strt = 0;
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

int	update_var(t_env_node *env, t_ipt_inf *arg_inf)
{
	char	*new_val;

	if (arg_inf->sep == '+')
	{
		new_val = ft_strjoin(env->val, arg_inf->val);
		if (!new_val)
			return (error_allocation());
		if (env->val)
			free(env->val);
		env->val = new_val;
	}
	else
	{
		new_val = arg_inf->val;
		if (env->val)
			free(env->val);
		env->val = new_val;
		
	}
	if (new_val != arg_inf->val)
		reset_inf(arg_inf);
	else
		free(arg_inf->key);
	return (1);
}

int	exist_var(t_env_node *env, t_ipt_inf *inf_arg)
{
	while (env)
	{
		if (!ft_strcmp(env->key, inf_arg->key))
		{
			if (inf_arg->val)
				return (update_var(env, inf_arg));
			else
			{
				reset_inf(inf_arg);
				return (1);
			}
		}
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
		tmp->key = inf_arg->key;
		tmp->val = inf_arg->val;
		change_ptrs(last, tmp, env);
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

/// this builtin can't have (export ARG++23), the sintax is not correct, so we have
// to handle with this, maybe in expand part??
// --> same to (export ZA,ZB)

void	export(t_word *word_lst, t_env_node **env_lst)
{
	t_ipt_inf	inf_arg;

	if (!word_lst->next)
		sort_env(*env_lst);
	else
	{
		ft_bzero(&inf_arg, sizeof(t_ipt_inf));
		word_lst = word_lst->next;
		while (word_lst)
		{
			if (set_inf(word_lst->word, &inf_arg) == -1)
			{
				error_allocation();
				return ;
			}
			if (add_var(env_lst, &inf_arg) == -1)
				return ;
			word_lst = word_lst->next;
		}
	}
}
