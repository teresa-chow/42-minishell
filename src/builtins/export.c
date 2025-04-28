/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 21:13:12 by carlaugu          #+#    #+#             */
/*   Updated: 2025/04/17 11:05:06 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include "../../include/utils.h"
#include "../../include/errors.h"

static int	update_var(t_env_node *env, t_input_inf *arg_inf, t_data *data);
static int	exist_var(t_input_inf *inf_arg, t_data *data);
static void	change_ptrs(t_env_node *last, t_env_node *tmp, t_env_node **env);

void	export(t_data *data, t_word *word)
{
	int	exit;

	exit = -1;
	if (!word->next)
		sort_env(data);
	else
		handle_with_args(word->next, data, &exit);
	if (exit == -1)
		data->exit_status = 0;
	else
		data->exit_status = exit;
	data->has_redir = false;
	data->has_vars = false;
}

int	add_var(t_input_inf *inf_arg, t_data *data)
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
			return (error_allocation(data));
		tmp->key = inf_arg->key;
		tmp->val = inf_arg->val;
		change_ptrs(last, tmp, &data->env);
	}
	return (0);
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
