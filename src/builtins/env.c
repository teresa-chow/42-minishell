/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/04/30 14:29:41 by tchow-so         ###   ########.fr       */
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
