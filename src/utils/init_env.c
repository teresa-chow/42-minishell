/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 21:12:51 by carlaugu          #+#    #+#             */
/*   Updated: 2025/03/20 12:09:11 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"
#include "../../include/builtins.h"
#include "../../include/errors.h"

static void	change_ptrs(t_env_node *last, t_env_node *tmp)
{
	if (last)
	{
		last->next = tmp;
		tmp->prev = last;
	}
}
static int	creat_env(t_data *data)
{
	char	*keys[] = {"OLDPWD", "PWD", "SHLVL", 0};
	t_env_node *tmp;
	t_env_node *last;
	int	i;
	
	i = -1;
	while (keys[++i])
	{
		last = last_node(data->env);
		tmp = ft_calloc(sizeof(t_env_node), sizeof(char));
		if (!tmp)
			return (free_env_list(data, 1, &data->env));
		if (!(*data).env)
			(*data).env = tmp;
		if (!ft_strcmp(keys[i], "PWD"))
			tmp->val = getcwd(NULL, 0);
		else if (!ft_strcmp(keys[i], "SHLVL"))
			tmp->val = ft_strdup("1");
		tmp->key = ft_strdup(keys[i]);
		if (!tmp->key || (ft_strcmp(keys[i], "OLDPWD") && !tmp->val))
			return (free_env_list(data, 1, &data->env));
		change_ptrs(last, tmp);
	}
	return (0);
}

static void	check_shlvl(t_env_node *tmp)
{
	char	*box;
	int	n;

	box = NULL;
	n = 0;
	if (!ft_strcmp(tmp->key, "SHLVL"))
	{
		n = ft_atoi(tmp->val) + 1;
		box = ft_itoa(n);
		if (box)
		{
			free(tmp->val);
			tmp->val = box;
		}
	}
}
int	find_oldpwd(t_data *data, t_env_init *env_init)
{
	if (!get_var(data->env, "OLDPWD"))
	{
		env_init->oldpwd = ft_calloc(sizeof(t_env_node), sizeof(char));
		if (!env_init->oldpwd)
			return (free_env_list(data, 1, &data->env));
		env_init->oldpwd->key = ft_strdup("OLDPWD");
		if (!env_init->oldpwd->key)
			return (free_env_list(data, 1, &data->env));
		change_ptrs(env_init->last, env_init->oldpwd);
	}
	return (0);
}

int	init_env_lst(char **envp, t_data *data)
{
	int	i;
	t_env_init	env_init;

	i = -1;
	env_init.last = NULL;
	if (!envp || !*envp)
		return(creat_env(data));
	while (envp && envp[++i])
	{
		if(set_inf(envp[i], &env_init.inf, data) == -1)
			return (free_env_list(data, 1, &data->env));
		env_init.tmp = ft_calloc(sizeof(t_env_node), sizeof(char));
		if (!env_init.tmp)
			return (free_env_list(data, 1, &data->env));	
		if (!data->env)
			data->env = env_init.tmp;
		env_init.tmp->key = env_init.inf.key;
		env_init.tmp->val = env_init.inf.val;
		check_shlvl(env_init.tmp);
		change_ptrs(env_init.last, env_init.tmp);
		env_init.last = env_init.tmp;
	}
	return (find_oldpwd(data, &env_init));
}
