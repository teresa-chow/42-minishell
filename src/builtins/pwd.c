/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 22:28:24 by carlaugu          #+#    #+#             */
/*   Updated: 2025/04/30 16:52:11 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include "../../include/errors.h"

void	pwd(t_data *data)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		perror("minishell");
		data->exit_status = ERR;
	}
	else
	{
		ft_putendl_fd (path, STDOUT_FILENO);
		free(path);
		data->exit_status = 0;
	}
}
