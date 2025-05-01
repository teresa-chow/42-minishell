/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 10:59:18 by tchow-so          #+#    #+#             */
/*   Updated: 2025/05/01 11:03:17 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execute.h"
#include "../../include/expand.h"
#include "../../include/utils.h"
#include "../../include/errors.h"

static int	handle_heredoc(char *eof, t_data *data, int old_in);
static int	set_pipe_and_fork(int *fd, pid_t *pid);
static void	handle_input(int *fd, char *eof, t_data *data);
static int	finalyze_handle_input(char *input, t_data *data,
				t_word *doc_word, char *eof, int *fd);

int	redir_heredoc(t_data *data, t_word *word)
{
	char	*eof;
	int		old_in;
	int		count;

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
			if (handle_heredoc(eof, data, old_in) != 0)
			{
				close(old_in); /// add
				return (-1);
			}
		}
		word = word->next;
	}
	close(old_in);
	return (0);
}

static int	handle_heredoc(char *eof, t_data *data, int old_in)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	status = 0;
	g_global = 0; // add
	if (set_pipe_and_fork(fd, &pid) == -1)
		return (-1);
	if (pid == 0)
	{
		data->exit_status = 0; // add
		handle_input(fd, eof, data); //// add this block
		if (g_global == SIGINT)
			data->exit_status = 130;
		close(old_in);
		exit (data->exit_status);
	}
	else
		parent_handle(fd, data, pid, status); // add this because norm
	return (data->exit_status);
}

void	handle_sign_child(int i)
{
	write (1, "\n", 1);
	if (i == SIGINT)
		g_global = SIGINT; //change this
	rl_replace_line("", 0);
	close(STDIN_FILENO); // add this
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
	t_word	*doc_word;

	signal(SIGINT, handle_sign_child);
	doc_word = NULL;
	if (verify_quotes(&eof, &data->quotes, data) == -1)
		return ;
	close(fd[0]);
	input = readline("> ");
	while (input && ft_strcmp(input, eof))
	{
		if (!data->quotes)
		{
			if (build_heredoc_wrd(&doc_word, input, data) == -1)
				return ;
		}
		else
			ft_putendl_fd(input, fd[1]);
		free(input);
		input = readline("> ");
	}
	if (finalyze_handle_input(input, data, doc_word, eof, fd) == -1)
		return ;
}

static int	finalyze_handle_input(char *input, t_data *data,
				t_word *doc_word, char *eof, int *fd)
{
	if (!input && g_global != SIGINT)
		heredoc_error(eof);
	if (!data->quotes && input)
	{
		data->in_heredoc = true; ///// add this change
		if (handle_tokens(doc_word, data, NULL) == -1)
			return (-1);
		data->in_heredoc = false; //////add this change
		print_to_pipe(doc_word, fd);
	}
	else if (input)
		free (eof);
	free_env_list(data, 0, &data->env);
	free_ast(&data->ast_root);
	free_words(&doc_word);
	free(input);
	close(fd[1]);
	close(data->old_stdin);
	close(data->old_stdout);
	data->quotes = false;
	return (0);
}
