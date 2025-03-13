/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 11:32:22 by carlaugu          #+#    #+#             */
/*   Updated: 2025/03/12 11:36:19 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/builtins.h"

void	env_cmd(t_env_node *env)
{
	char	*equal;

	while (env)
	{
		equal = ft_strchr(env->val, '=');
		if (equal)
		{
			ft_putstr_fd(env->key, 1);
			ft_putendl_fd(env->val, 1);
		}
		env = env->next;
	}
}