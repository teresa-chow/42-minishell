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
	while (env)
	{
		if (env->val)
		{
			ft_putstr_fd(env->key, 1);
			write (1, "=", 1);
			ft_putendl_fd(env->val, 1);
		}
		env = env->next;
	}
}