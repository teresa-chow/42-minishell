/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:46:49 by tchow-so          #+#    #+#             */
/*   Updated: 2025/05/08 14:37:41 by carlaugu         ###   ########.fr       */
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

void	reset_old_in_out(t_data *data, t_tree_node *node)
{
	if (node->fd_in != -1)
		close(node->fd_in);
	if (node->fd_out != -1)
		close(node->fd_out);
	node->fd_in = -1;
	printf("reset_old_in_out: node.fd_in ficou a %d com %s %s\n", node->fd_in, node->word->word, node->word->next->word);
	node->fd_out = -1;
	printf("reset_old_in_out: node.fd_in ficou a %d\n", node->fd_out);
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
	// free(data->redir);
	// data->redir = NULL;
}
