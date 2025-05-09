/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 10:59:18 by tchow-so          #+#    #+#             */
/*   Updated: 2025/05/09 11:08:34 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execute.h"
#include "../../include/expand.h"
#include "../../include/utils.h"
#include "../../include/errors.h"

static int	handle_heredoc(char *eof, t_data *data, t_tree_node *node);
static int	set_pipe_and_fork(int *fd, pid_t *pid);
static void	handle_input(int *fd, char *eof, t_data *data);
static int	finalize_handle_input(char *input, t_data *data, char *eof,
				int *fd);

int	redir_heredoc(t_data *data, t_tree_node *node)
{
	char	*eof;
	t_word	*word;

	word = node->word;
	while (word)
	{
		if (word->redir == HEREDOC)
		{
			if (node->fd_in != -1)
			{
				close(node->fd_in);
				node->fd_in = -1;
			}
			eof = word->next->word;
			if (handle_heredoc(eof, data, node) != 0)
				return (-1);
		}
		word = word->next;
	}
	return (0);
}

static int	handle_heredoc(char *eof, t_data *data, t_tree_node *node)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	status = 0;
	g_global = 0;
	if (set_pipe_and_fork(fd, &pid) == -1)
		return (-1);
	if (pid == 0)
	{
		close_heredoc_fds(data, NULL);
		data->exit_status = 0;
		handle_input(fd, eof, data);
		if (g_global == SIGINT)
			data->exit_status = 130;
		exit(data->exit_status);
	}
	else
	{
		node->fd_in = dup(fd[0]);
		close(fd[0]);
		parent_handle(fd, data, pid, status);
	}
	return (data->exit_status);
}

static int	set_pipe_and_fork(int *fd, pid_t *pid)
{
	if (pipe(fd) == -1)
	{
		ft_putstr_fd("Minishell: pipe error\n", STDERR_FILENO);
		return (-1);
	}
	*pid = fork();
	if (*pid == -1)
	{
		ft_putstr_fd("Minishell: fork error\n", STDERR_FILENO);
		return (-1);
	}
	return (0);
}

static void	handle_input(int *fd, char *eof, t_data *data)
{
	char	*input;

	signal(SIGINT, handle_sign_child);
	if (verify_quotes(&eof, &data->quotes, data) == -1)
		return ;
	close(fd[0]);
	input = readline("> ");
	while (input && ft_strcmp(input, eof))
	{
		if (!data->quotes)
		{
			if (build_heredoc_wrd(input, data) == -1)
				return ;
		}
		else
			ft_putendl_fd(input, fd[1]);
		free(input);
		input = readline("> ");
	}
	if (finalize_handle_input(input, data, eof, fd) == -1)
		return ;
}

static int	finalize_handle_input(char *input, t_data *data, char *eof,
	int *fd)
{
	if (!input && g_global == 0)
		heredoc_error(eof);
	if (!data->quotes && input)
	{
		data->in_heredoc = true;
		if (handle_tokens(data->doc_word, data, NULL) == -1)
			return (-1);
		data->in_heredoc = false;
		print_to_pipe(data->doc_word, fd);
	}
	else if (input)
		free (eof);
	free_env_list(data, 0, &data->env);
	free_ast(&data->ast_root);
	free_words(&data->doc_word);
	free(input);
	close(fd[1]);
	data->quotes = false;
	return (0);
}
