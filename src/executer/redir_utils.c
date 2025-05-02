/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:46:49 by tchow-so          #+#    #+#             */
/*   Updated: 2025/05/02 21:08:39 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/execute.h"
#include "../../include/utils.h"

void	save_old_in_out(t_data *data)
{
	data->old_stdin = dup(STDIN_FILENO);
	data->old_stdout = dup(STDOUT_FILENO);
}

void	reset_old_in_out(t_data *data)
{
	if (data->redir)
	{
		if (data->redir->in)
			close(data->redir->fd_in);
		if (data->redir->out)
			close(data->redir->fd_out);
	}
	if (dup2(data->old_stdin, STDIN_FILENO) == -1)
	{
		perror("minishell: dup2");
		return ;
	}
	close(data->old_stdin);
	if (dup2(data->old_stdout, STDOUT_FILENO) == -1)
	{
		perror("minishell: dup2");
		return ;
	}
	close(data->old_stdout);
	free(data->redir);
	data->redir = NULL;
}
