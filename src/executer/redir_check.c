/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 09:57:22 by carlaugu          #+#    #+#             */
/*   Updated: 2025/05/02 16:21:52 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/execute.h"
#include "../../include/errors.h"
#include "../../include/utils.h"

static int	is_redirect(t_word *word);
static int	handle_redir( t_data *data, t_word *word);
static int	handle_redir_in(t_data *data, t_word *word);
static int	handle_redir_out(t_data *data, t_word *word);

int	redir_check(t_word *word, t_data *data)
{
	t_word			*tmp;

	if (!word)
		return (0);
	tmp = word;
	data->redir = ft_calloc(1, sizeof(t_redir_check));
	if (!is_redirect(word))
		return (0);
	if (handle_redir(data, tmp) == -1)
	{
		reset_old_in_out(data);
		return (-1);
	}
	return (0);
}

static int	is_redirect(t_word *word)
{
	t_word	*tmp;

	tmp = word;
	while (tmp)
	{
		if (tmp->redir == IN || tmp->redir == OUT || tmp->redir == APPEND)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

static int	handle_redir(t_data *data, t_word *word)
{
	while (word)
	{
		if ((word->redir != NONE && word->redir != HEREDOC) && word->next)
		{
			if (word->redir == IN)
			{
				if (data->redir->in)
					close(data->redir->fd_in);
				data->redir->in = 0;
				if (handle_redir_in(data, word->next) == -1)
					return (-1);
			}
			if (word->redir == OUT || word->redir == APPEND)
			{
				if (data->redir->out)
					close(data->redir->fd_out);
				data->redir->out = 0;
				if (handle_redir_out(data, word) == -1)
					return (-1);
			}
		}
		word = word->next;
	}
	return (0);
}

static int	handle_redir_in(t_data *data, t_word *word)
{
	if (!access(word->word, F_OK))
	{
		if (access(word->word, R_OK) == -1)
		{
			print_fd(STDERR_FILENO, "minishell: %s: ", word->word);
			perror("");
			data->exit_status = ERR;
			return (-1);
		}
		if (redir_in(data, word) == -1)
			return (-1);
	}
	else
		return (no_file_or_dir(word->word, data, 1), -1);
	data->redir->in = 1;
	return (0);
}

static int	handle_redir_out(t_data *data, t_word *word)
{
	if (!access(word->word, F_OK))
	{
		if (access(word->word, W_OK) == -1)
		{
			print_fd(STDERR_FILENO, "minishell: %s: ", word->word);
			perror("");
			data->exit_status = ERR;
			return (-1);
		}
	}
	if (redir_out(data, word) == -1)
		return (-1);
	data->redir->out = 1;
	return (0);
}
