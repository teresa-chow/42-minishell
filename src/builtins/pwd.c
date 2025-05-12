/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 22:28:24 by carlaugu          #+#    #+#             */
/*   Updated: 2025/05/09 10:59:40 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include "../../include/errors.h"

void	pwd(t_data *data)
{
	char		*path;
	t_env_node	*pwd;

	pwd = ft_getenv(data->env, "PWD");
	path = getcwd(NULL, 0);
	if (!path)
	{
		if (pwd && pwd->val)
			ft_putendl_fd (pwd->val, STDOUT_FILENO);
		else
		{
			perror("minishell");
			data->exit_status = ERR;
		}
	}
	else
	{
		ft_putendl_fd (path, STDOUT_FILENO);
		free(path);
		data->exit_status = 0;
	}
}
