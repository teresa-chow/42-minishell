/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 22:28:24 by carlaugu          #+#    #+#             */
/*   Updated: 2025/04/30 15:02:43 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

void	pwd(t_data *data)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		perror("minishell");
		data->exit_status = 1;
	}
	else
	{
		ft_putendl_fd (path, STDOUT_FILENO);
		free(path);
		data->exit_status = 0;
	}
}
