/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-28 16:52:48 by carlaugu          #+#    #+#             */
/*   Updated: 2025-03-28 16:52:48 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

t_env_node	*last_node(t_env_node *env_lst)
{
	while (env_lst)
	{
		if (!env_lst->next)
			break ;
		env_lst = env_lst->next;
	}
	return (env_lst);
}

t_env_node	*ft_getenv(t_env_node *env, char *key)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env);
		env = env->next;
	}
	return (NULL);
}
