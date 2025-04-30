/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 10:59:18 by tchow-so          #+#    #+#             */
/*   Updated: 2025/04/30 12:29:16 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execute.h"
#include "../../include/expand.h"
#include "../../include/utils.h"
#include "../../include/errors.h"

static int	handle_heredoc(char *eof, t_data *data);
static int	set_pipe_and_fork(int *fd, pid_t *pid);
static int	handle_input(int *fd, char *eof, t_data *data);
static int	finalyze_handle_input(char *input, t_data *data, \
	t_word *doc_word, char *eof, int *fd);

int	redir_heredoc(t_data *data, t_word *word)
{
	char	*eof;
	int	old_in;
	int	count;

	count = 0;
	old_in = dup(STDIN_FILENO);
	while (word)
	{
		if (word->redir == HEREDOC)
		{
			count++;
			if (count > 1)
				dup2(old_in, STDIN_FILENO);
			eof = word->next->word;
			if (handle_heredoc(eof, data) != 0)
				return (-1);
		}
		word = word->next;
	}
	close(old_in);
	return (0);
}

static int	handle_heredoc(char *eof, t_data *data)
{
	int	fd[2];
	pid_t	pid;
	int	status;

	if (set_pipe_and_fork(fd, &pid) == -1)
		return (-1);
	if (pid == 0)
	{
		if (handle_input(fd, eof, data) != 0)
			exit (1);
		exit(0);
	}
	else
	{
		close(fd[1]);
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		signal(SIGINT, handle_signal);
		set_exit_status(&status, data);
		if (data->exit_status > 128)
			return (data->exit_status);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
	return(data->exit_status);
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

static int	handle_input(int *fd, char *eof, t_data *data)
{
	char	*input;
	t_word	*doc_word;

	signal(SIGINT, SIG_DFL);
	doc_word = NULL;
	if (verify_quotes(&eof, &data->quotes, data) == -1)
		return (-1);
	close(fd[0]);
	input = readline("> ");
	while (input && ft_strcmp(input, eof))
	{
		if (!data->quotes)
		{
			if (build_heredoc_wrd(&doc_word, input, data) == -1)
				return (-1);
		}
		else
			ft_putendl_fd(input, fd[1]);
		free(input);
		input = readline("> ");
	}
	if (finalyze_handle_input(input, data, doc_word, eof, fd) == -1)
		return (-1);
	return (0);
}

static int	finalyze_handle_input(char *input, t_data *data, \
	t_word *doc_word, char *eof, int *fd)
{
	if (!input)
		heredoc_error(eof);
	else
	if (!data->quotes)
	{
		if (handle_tokens(doc_word, data, NULL) == -1)
			return (-1);
		print_to_pipe(doc_word, fd);
	}
	else
		free (eof);
	free_words(&doc_word);
	free(input);
	close(fd[1]);
	data->quotes = false;
	return (0);
}
