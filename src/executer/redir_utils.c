/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:46:49 by tchow-so          #+#    #+#             */
/*   Updated: 2025/05/09 11:39:26 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/execute.h"
#include "../../include/utils.h"

static void	close_node_fd(t_tree_node *node);

void	save_old_in_out(t_data *data)
{
	data->old_stdin = dup(STDIN_FILENO);
	data->old_stdout = dup(STDOUT_FILENO);
}

void	reset_old_in_out(t_data *data, t_tree_node *node)
{
	close_node_fd(node);
	if (data->old_stdin != -1)
	{
		if (dup2(data->old_stdin, STDIN_FILENO) == -1)
		{
			perror("minishell: dup2");
			return ;
		}
		close(data->old_stdin);
		data->old_stdin = -1;
	}
	if (data->old_stdout != -1)
	{
		if (dup2(data->old_stdout, STDOUT_FILENO) == -1)
		{
			perror("minishell: dup2");
			return ;
		}
		close(data->old_stdout);
		data->old_stdout = -1;
	}
}

static void	close_node_fd(t_tree_node *node)
{
	if (node->fd_in != -1)
	{
		close(node->fd_in);
		node->fd_in = -1;
	}
	if (node->fd_out != -1)
	{
		close(node->fd_out);
		node->fd_out = -1;
	}
}
