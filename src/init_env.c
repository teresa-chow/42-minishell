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

static void	change_ptrs(t_env_node **env, t_env_node *last, t_env_node *tmp)
{
	if (last)
	{
		last->next = tmp;
		tmp->prev = last;
	}
	if (!*env)
		*env = tmp;
}	
static int	creat_env(t_env_node **env)
{
	char	*keys[] = {"OLDPWD", "PWD=", "SHLVL=", 0};
	t_env_node *tmp;
	t_env_node *last;
	int	i;
	
	i = -1;
	while (keys[++i])
	{
		last = get_last(*env);
		tmp = ft_calloc(sizeof(t_env_node), sizeof(char));
		if (!tmp)
			return (free_env_list(*env, 1));
		if (!ft_strcmp(keys[i], "PWD="))
			tmp->val = getcwd(NULL, 0);
		else if (!ft_strcmp(keys[i], "SHLVL="))
			tmp->val = ft_strdup("1");
		else if (!ft_strcmp(keys[i], "OLDPWD"))
			tmp->val = ft_strdup("");
		tmp->key = ft_strdup(keys[i]);
		if (!tmp->key || !tmp->val)
			return (free_env_list(*env, 1));
		change_ptrs(env, last, tmp);
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
		n = ft_atoi(ft_strchr(tmp->val, '=') + 1) + 1;
		box = tmp->val;
		tmp->val = ft_itoa(n);
		if (!tmp->val)
			tmp->val = box;
		else
			free(box);
	}
}

char	find_sep_a(char *s) // this is duplicate by export
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

int	set_inf_a(char *word, t_ipt_inf *inf_arg) // this is duplicate by export
{
	inf_arg->sep = find_sep_a(word);
	inf_arg->key = ft_substr(word, 0, ft_strlen(word) - ft_strlen(ft_strchr(word, inf_arg->sep)));
	if (!inf_arg->key)
		return (-1);
	inf_arg->val_strt = ft_strlen(word) - ft_strlen(ft_strchr(word, '='));
	inf_arg->val = ft_substr(word, inf_arg->val_strt, ft_strlen(ft_strchr(word, '=')));
	if (!inf_arg->val)
	{
		free(inf_arg->key);
		return (-1);
	}
	return (0);
}
int	init_env_lst(char **envp, t_env_node **env_lst)
{
	int	i;
	t_env_node	*tmp;
	t_env_node	*last;
	t_ipt_inf	inf;

	i = -1;
	last = NULL;
	if (!envp || !*envp)
		return(creat_env(env_lst));	
	while (envp && envp[++i])
	{
		if(set_inf_a(envp[i], &inf) == -1)
			return (free_env_list(*env_lst, 1));
		tmp = ft_calloc(sizeof(t_env_node), sizeof(char));
		if (!tmp)
			return (free_env_list(*env_lst, 1));
		tmp->key = inf.key;
		tmp->val = inf.val;
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
