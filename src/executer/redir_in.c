/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:24:51 by carlaugu          #+#    #+#             */
/*   Updated: 2025/04/30 18:56:16 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execute.h"
#include "../../include/errors.h"
#include "../../include/utils.h"

static int	get_fd(t_word *word, int *fd, t_data *data);
static int	open_new_file(t_data *data, t_word *word, int *fd);
static void	redirect_stdin(int *fd, int i);

int	redir_in(t_word *word, t_data *data)
{
	int	fd;

	fd = 0;
	if (get_fd(word, &fd, data) == -1)
		return (-1);
	redirect_stdin(&fd, 0);
	return (0);
}

static int	get_fd(t_word *word, int *fd, t_data *data)
{
	while (word)
	{
		if (word->redir == IN && word->next)
		{
			if (*fd)
			{
				if (close(*fd) < 0)
				{
					perror("minishell: close");
					data->exit_status = ERR;
					return (-1);
				}
			}
			if (open_new_file(data, word->next, fd) == -1)
				return (-1);
		} 
		word = word->next;
	}
	return (0);
}

static int	open_new_file(t_data *data, t_word *word, int *fd)
{
	*fd = open(word->word, O_RDONLY);
	if (*fd < 0)
	{
		print_fd(STDERR_FILENO, "minishell: %s: ", word->next->word);
		perror("");
		data->exit_status = ERR;
		return (-1);
	}
	return (0);
}

static void	redirect_stdin(int *fd, int i)
{
	if (dup2(fd[i], STDIN_FILENO) == -1)
	{
		perror("minishell: dup2");
		return ;
	}
}
