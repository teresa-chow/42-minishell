/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 21:12:51 by carlaugu          #+#    #+#             */
/*   Updated: 2025/03/11 14:21:58 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"
#include "../include/builtins.h"
#include "../include/errors.h"

static void	change_ptrs(t_env_node **env, t_env_node *last, char *val, t_env_node *tmp)
{
	if (last)
	{
		last->next = tmp;
		tmp->prev = last;
	}
	if (!*env)
		*env = tmp;
	if (val)
		free(val);
}	
static int	creat_env(t_env_node **env)
{
	char	*keys[] = {"OLDPWD", "PWD=", "SHLVL=", 0};
	char	*val;
	t_env_node *tmp;
	t_env_node *last;
	int	i;
	
	val = NULL;
	i = -1;
	while (keys[++i])
	{
		last = get_last(*env);
		tmp = ft_calloc(sizeof(t_env_node), sizeof(char));
		if (!tmp)
			return (free_env_list(*env, 1));
		if (!ft_strcmp(keys[i], "PWD="))
			val = getcwd(NULL, 0);
		else if (!ft_strcmp(keys[i], "SHLVL="))
			val = ft_strdup("1");
		tmp->var = ft_strjoin(ft_strdup(keys[i]), val);
		if (!tmp->var)
			return (free_env_list(*env, 1));
		change_ptrs(env, last, val, tmp);
	}
	return (0);
}

static void	check_return(t_env_node *tmp, char **box)
{
	if (!tmp->var)
		tmp->var = *box;
	else
		free(*box);
}

static void	check_shlvl(t_env_node *tmp)
{
	char	*key;
	char	*val;
	char	*box;
	int	n;

	key = ft_substr(tmp->var, 0, ft_strlen(tmp->var) - ft_strlen(ft_strchr(tmp->var, '=') + 1));
	if (!key)
		return ;
	if (!ft_strcmp(key, "SHLVL="))
	{
		val = ft_substr(tmp->var, 6, ft_strlen(ft_strchr(tmp->var, '=') + 1));
		if (!val)
		{
			free(key);
			return ;
		}
		n = ft_atoi(val) + 1;
		box = tmp->var;
		tmp->var = ft_strjoin(key, ft_itoa(n));
		check_return(tmp, &box);
		free(val);
	}
	free(key);
}
int	init_env_lst(char **envp, t_env_node **env_lst)
{
	int	i;
	t_env_node	*tmp;
	t_env_node	*last;

	i = -1;
	last = NULL;
	if (!envp || !*envp)
		return(creat_env(env_lst));	
	while (envp && envp[++i])
	{
		tmp = ft_calloc(sizeof(t_env_node), sizeof(char));
		if (!tmp)
			return (free_env_list(*env_lst, 1));
		tmp->var = ft_strdup(envp[i]);
		if (!tmp->var)
		return (free_env_list(*env_lst, 1));
		check_shlvl(tmp);
		if (last)
			last->next = tmp;
		tmp->prev = last;
		if (!*env_lst)
			*env_lst = tmp;
		last = tmp;
	}
	return (0);
}
