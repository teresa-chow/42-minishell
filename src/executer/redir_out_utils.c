/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:45:35 by tchow-so          #+#    #+#             */
/*   Updated: 2025/04/16 15:15:32 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/execute.h"
#include "../../include/utils.h"

void	redirect_stdout(int *fd, int i)
{
	if (dup2(fd[i], STDOUT_FILENO) == -1)
	{
		perror("minishell: dup2");
		return ;
	}
}

void	close_fd(int *fd, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		close(fd[i]);
		i++;
	}
	if (count)
		free(fd);
}