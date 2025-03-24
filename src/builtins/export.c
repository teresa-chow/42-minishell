/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 21:13:12 by carlaugu          #+#    #+#             */
/*   Updated: 2025/03/20 14:31:19 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include "../../include/utils.h"
#include "../../include/errors.h"

static int	update_var(t_env_node *env, t_input_inf *arg_inf, t_data *data);
static int	exist_var(t_input_inf *inf_arg, t_data *data);
static void	change_ptrs(t_env_node *last, t_env_node *tmp, t_env_node **env);
static int	add_var(t_input_inf *inf_arg, t_data *data);

void	export(t_data *data, t_word_lst *word_lst)
{
	t_input_inf	inf_arg;
	t_word		*word;

	word = word_lst->word;
	if (!word->next)
		sort_env(data);
	else
	{
		ft_bzero(&inf_arg, sizeof(t_input_inf));
		word = word->next;
		while (word)
		{
			if (set_inf(word->word, &inf_arg, data) == -1)
			{
				error_allocation(data);
				return ;
			}
			if (add_var(&inf_arg, data) == -1)
				return ;
			word = word->next;
		}
	}
}

static int	update_var(t_env_node *env, t_input_inf *arg_inf, t_data *data)
{
	char	*new_val;

	if (arg_inf->sep == '+')
	{
		new_val = ft_strjoin(env->val, arg_inf->val);
		if (!new_val)
			return (error_allocation(data));
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

static int	exist_var(t_input_inf *inf_arg, t_data *data)
{
	t_env_node	*env;

	env = data->env;
	while (env)
	{
		if (!ft_strcmp(env->key, inf_arg->key))
		{
			if (inf_arg->val)
				return (update_var(env, inf_arg, data));
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

static int	add_var(t_input_inf *inf_arg, t_data *data)
{
	int			check;
	t_env_node	*last;
	t_env_node	*tmp;

	check = exist_var(inf_arg, data);
	if (check == -1 || check == 1)
		return (check);
	else
	{
		last = last_node(data->env);
		tmp = ft_calloc(sizeof(t_env_node), sizeof(char));
		if (!tmp)
			return (-1);
		tmp->key = inf_arg->key;
		tmp->val = inf_arg->val;
		change_ptrs(last, tmp, &data->env);
	}
	return (0);
}
