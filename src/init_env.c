/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-10 21:12:51 by carlaugu          #+#    #+#             */
/*   Updated: 2025-03-10 21:12:51 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"
#include "../include/builtins.h"

void	creat_env(t_env_node **env)
{
	char	*keys[] = {"OLDPWD", "PWD=", "SHLVL=", 0};
	t_env_node *tmp;
	char	*val;
	t_env_node *last;
	int	i;

	val = NULL;
	i = -1;
	while (keys[++i])
	{
		last = get_last(*env);
		tmp = ft_calloc(sizeof(t_env_node), sizeof(char));
		// if (!tmp) ----------------------------------------->>> if fail, i can call error_allocation();
		if (!ft_strcmp(keys[i], "PWD="))
			val = getcwd(NULL, 0);
		else if (!ft_strcmp(keys[i], "SHLVL="))
			val = ft_strdup("1");
		tmp->var = ft_strjoin(ft_strdup(keys[i]), val);
		// if (!tmp->var)
		if (last)
		{
			last->next = tmp;
			tmp->prev = last;
		}
		if (!*env)
			*env = tmp;
		free(val);
	}
}

int	init_env_lst(char **envp, t_env_node **env_lst)
{
	int	i;
	t_env_node	*tmp;
	t_env_node	*last;

	i = -1;
	last = NULL;
	if (!envp || !*envp)
	{
		creat_env(env_lst);	
		return (0);
	}
	while (envp && envp[++i])
	{
		tmp = ft_calloc(sizeof(t_env_node), sizeof(char));
		if (!tmp)
		{
			free_env_list(*env_lst);
			return (0);
		}
		tmp->var = ft_strdup(envp[i]);
		if (last)
			last->next = tmp;
		tmp->prev = last;
		if (!*env_lst)
			*env_lst = tmp;
		last = tmp;
	}
	return (1);
}