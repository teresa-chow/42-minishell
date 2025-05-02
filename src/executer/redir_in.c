/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:24:51 by carlaugu          #+#    #+#             */
/*   Updated: 2025/05/02 16:15:43 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execute.h"
#include "../../include/errors.h"
#include "../../include/utils.h"

static int	open_new_file(t_data *data, t_word *word);
static void	redirect_stdin(int fd);

int	redir_in(t_data *data, t_word *word)
{
	if (open_new_file(data, word) == -1)
		return (-1);
	return (0);
}

static int	open_new_file(t_data *data, t_word *word)
{
	data->redir->fd_in = open(word->word, O_RDONLY);
	if (data->redir->fd_in < 0)
	{
		print_fd(STDERR_FILENO, "minishell: %s: ", word->next->word);
		perror("");
		data->exit_status = ERR;
		return (-1);
	}
	else
		redirect_stdin(data->redir->fd_in);
	return (0);
}

static void	redirect_stdin(int fd)
{
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("minishell: dup2");
		return ;
	}
}
