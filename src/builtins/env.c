/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 11:32:22 by carlaugu          #+#    #+#             */
/*   Updated: 2025/04/10 14:56:26 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

void	env_cmd(t_env_node *env, t_data *data)
{
	while (env)
	{
		if (env->val)
		{
			ft_putstr_fd(env->key, 1);
			ft_putendl_fd(env->val, 1);
		}
		env = env->next;
	}
	data->exit_status = 0;
}
