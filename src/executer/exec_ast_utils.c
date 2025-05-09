/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:08:53 by tchow-so          #+#    #+#             */
/*   Updated: 2025/05/08 13:45:22 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/builtins.h"
#include "../../include/execve.h"
#include "../../include/errors.h"

static void	exec_fork_child(t_data *data, t_tree_node *node);

int	cd_arg_check(t_word *word, t_data *data)
{
	if (word->next && word->next->next
		&& word->next->next->redir == NONE)
	{
		cd_error(NULL, data, 0);
		return (0);
	}
	return (1);
}

void	exec_child(t_data *data, bool pipeline, t_tree_node *node)// add
{
	t_word	*tmp;

	tmp = node->word;
	while (tmp && tmp->redir != NONE)
		tmp = tmp->next->next;
	if (!tmp)
		return ;
	if (!pipeline)
		exec_fork_child(data, node);
	else
		exec_external(data, node->word, node);
}

static void	exec_fork_child(t_data *data, t_tree_node *node)
{
	int		status;
	pid_t	pid;

	status = 0;
	if (node->fd_in != -1)
	{
		dup2(node->fd_in, STDIN_FILENO);
		close(node->fd_in);
		node->fd_in = -1;
	}
	pid = fork();
	if (pid < 0)
	{
		perror("minishell");
		return ;
	}
	else if (pid == 0)
	{
		//if (node->fd_in != -1)
		//	close(node->fd_in);
		signal(SIGINT, SIG_DFL);
		exec_external(data, node->word, node);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		signal(SIGINT, handle_signal);
		set_exit_status(&status, data);
	}
}

void	set_exit_status(int *status, t_data *data)
{
	if (WIFEXITED(*status))
		data->exit_status = WEXITSTATUS(*status);
	else if (WIFSIGNALED(*status))
	{
		data->exit_status = 128 + WTERMSIG(*status);
		write (1, "\n", 1);
	}
}
