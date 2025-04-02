/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:52:48 by carlaugu          #+#    #+#             */
/*   Updated: 2025/04/02 16:40:14 by tchow-so         ###   ########.fr       */
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
	t_env_node *tmp;

	tmp = env ;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
