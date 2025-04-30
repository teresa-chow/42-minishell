/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:52:48 by carlaugu          #+#    #+#             */
/*   Updated: 2025/04/30 16:31:21 by tchow-so         ###   ########.fr       */
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
