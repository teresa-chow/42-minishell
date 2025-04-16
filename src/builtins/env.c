/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 11:32:22 by carlaugu          #+#    #+#             */
/*   Updated: 2025/04/16 10:36:36 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

void	env_cmd(t_env_node *env, t_data *data)
{
	while (env)
	{
		if (env->val)
		{
			ft_putstr_fd(env->key, STDOUT_FILENO);
			write (STDOUT_FILENO, "=", 1);
			ft_putendl_fd(env->val, STDOUT_FILENO);
		}
		env = env->next;
	}
	data->exit_status = 0;
}
