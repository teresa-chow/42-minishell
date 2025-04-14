/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:45:35 by tchow-so          #+#    #+#             */
/*   Updated: 2025/04/14 13:50:02 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/execute.h"
#include "../../include/utils.h"

void	redirect_stdout(int **fd, char **files, int i, int type)
{
	if (type == 1)
		(*fd)[i] = open(files[i], O_WRONLY | O_CREAT, 0644); //must check permissions of existing files
	else if (type == 2)
		(*fd)[i] = open(files[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if ((*fd)[i] == -1)
	{
		print_fd(STDERR_FILENO, "minishell: %s: ", files[i]);
		perror("");
		return ;
	}
	if (dup2((*fd)[i], STDOUT_FILENO) == -1)
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