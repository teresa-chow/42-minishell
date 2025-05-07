/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:24:51 by carlaugu          #+#    #+#             */
/*   Updated: 2025/05/07 23:28:39 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execute.h"
#include "../../include/errors.h"
#include "../../include/utils.h"

static int	open_new_file(t_data *data, t_tree_node *node, t_word *word,
	int tmp_in);
static void	redirect_stdin(int fd, int tmp_in);

int	redir_in(t_data *data, t_tree_node *node, t_word *word, int tmp_in)
{
	if (open_new_file(data, node, word, tmp_in) == -1)
		return (-1);
	return (0);
}

static int	open_new_file(t_data *data, t_tree_node *node, t_word *word,
	int tmp_in)
{
	node->fd_in = open(word->word, O_RDONLY);
	if (node->fd_in < 0)
	{
		print_fd(STDERR_FILENO, "minishell: %s: ", word->next->word);
		perror("");
		data->exit_status = ERR;
		return (-1);
	}
	redirect_stdin(node->fd_in, tmp_in);
	return (0);
}

static void	redirect_stdin(int fd, int tmp_in)
{
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("minishell: dup2");
		return ;
	}
	if (tmp_in != -1)
	{
		close(fd);
		dup2(tmp_in, STDIN_FILENO);
	}
	
}
