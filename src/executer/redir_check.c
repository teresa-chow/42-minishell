/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 09:57:22 by carlaugu          #+#    #+#             */
/*   Updated: 2025/05/08 14:02:19 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/execute.h"
#include "../../include/errors.h"
#include "../../include/utils.h"

static int	is_redirect(t_word *word);
static int	handle_redir(t_data *data, t_tree_node *node, t_word *word,
	int tmp_in);
static int	handle_redir_in(t_data *data, t_tree_node *node, t_word *word,
	int tmp_in);
static int	handle_redir_out(t_data *data, t_tree_node *node, t_word *word);

int	redir_check(t_tree_node *node, t_data *data)
{
	t_word			*tmp;
	int				tmp_in;

	if (!node->word)
		return (0);
	tmp = node->word;
	if (!is_redirect(node->word))
	{
		if (node->fd_in != -1)
		{
			dup2(node->fd_in, STDIN_FILENO);
			close(node->fd_in);
			node->fd_in = -1;
		}
		return (0);
	}
	tmp_in = -1;
	if (heredoc_redir_in(node))
		tmp_in = dup(node->fd_in);
	if (handle_redir(data, node, tmp, tmp_in) == -1)
	{
		if (tmp_in != -1)
			close(tmp_in);
		return (-1);
	}
	if (tmp_in != -1)
		close(tmp_in);
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

static int	handle_redir(t_data *data, t_tree_node *node, t_word *word,
	int tmp_in)
{
	while (word)
	{
		if (word->redir == IN)
		{
			if (node->fd_in != -1)
				close(node->fd_in);
			node->fd_in = -1;
			if (handle_redir_in(data, node, word->next, tmp_in) == -1)
				return (-1);
		}
		if (word->redir == OUT || word->redir == APPEND)
		{
			if (node->fd_out != -1)
				close(node->fd_out);
			node->fd_out = -1;
			if (handle_redir_out(data, node, word) == -1)
				return (-1);
		}
		word = word->next;
	}
	return (0);
}

static int	handle_redir_in(t_data *data, t_tree_node *node, t_word *word,
	int tmp_in)
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
		if (redir_in(data, node, word, tmp_in) == -1)
			return (-1);
	}
	else
		return (no_file_or_dir(word->word, data, 1), -1);
	return (0);
}

static int	handle_redir_out(t_data *data, t_tree_node *node, t_word *word)
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
	if (redir_out(data, node, word) == -1)
		return (-1);
	return (0);
}
