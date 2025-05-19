/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:11:15 by tchow-so          #+#    #+#             */
/*   Updated: 2025/05/19 11:46:37 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/execute.h"
#include "../../include/utils.h"
#include "../../include/errors.h"

static int	create_file(t_data *data, t_tree_node *node, t_word *word);
static void	redirect_stdout(int fd);

int	redir_out(t_data *data, t_tree_node *node, t_word *word)
{
	if (create_file(data, node, word) == -1)
		return (-1);
	return (0);
}

static int	create_file(t_data *data, t_tree_node *node, t_word *word)
{
	if (word->redir == OUT && word->next)
		node->fd_out
			= open(word->next->word, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (word->redir == APPEND && word->next)
		node->fd_out
			= open(word->next->word, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (node->fd_out < 0)
	{
		print_fd(STDERR_FILENO, "minishell: %s: ", word->next->word);
		perror("");
		data->exit_status = ERR;
		return (-1);
	}
	else
		redirect_stdout(node->fd_out);
	return (0);
}

static void	redirect_stdout(int fd)
{
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("minishell: dup2");
		return ;
	}
}
