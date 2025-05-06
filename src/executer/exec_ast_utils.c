/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:08:53 by tchow-so          #+#    #+#             */
/*   Updated: 2025/05/02 16:19:27 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/builtins.h"
#include "../../include/execve.h"
#include "../../include/errors.h"

static void	exec_fork_child(t_data *data, t_word *word);

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

void	exec_child(t_data *data, t_word *word, bool pipeline)
{
	t_word	*tmp;

	tmp = word;
	while (tmp && tmp->redir != NONE)
		tmp = tmp->next->next;
	if (!tmp)
		return ;
	if (!pipeline)
		exec_fork_child(data, word);
	else
		exec_external(data, word);
}

static void	exec_fork_child(t_data *data, t_word *word)
{
	int		status;
	pid_t	pid;

	status = 0;
	pid = fork();
	if (pid < 0)
	{
		perror("minishell");
		return ;
	}
	else if (pid == 0)
	{
		if (word->next->in_fd)
		{
			dup2(word->next->in_fd, STDIN_FILENO);
			close_heredoc_fds(data, NULL);
		}
		signal(SIGINT, SIG_DFL);
		exec_external(data, word);
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
