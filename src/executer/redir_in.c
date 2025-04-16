/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:24:51 by carlaugu          #+#    #+#             */
/*   Updated: 2025/04/16 17:08:12 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execute.h"
#include "../../include/errors.h"
#include "../../include/utils.h"

static int	check_file_exists(t_word *word, bool *has_in, t_data *data);
static int	get_fd(t_word *word, int *fd, t_data *data);
static void	redirect_stdin(int *fd, int i);

int	redir_in(t_word *word, t_data *data)
{
	int	fd;
	bool	has_in;

	if (!word->next)
		return (0);
	has_in = false;
	fd = 0;
	if (check_file_exists(word->next, &has_in, data) == -1)
		return (-1);
	if (has_in)
	{
		if (get_fd(word->next, &fd, data) == -1)
			return (-1);
		redirect_stdin(&fd, 0);
	}
	return (0);
}

static int	check_file_exists(t_word *word, bool *has_in, t_data *data)
{
	while (word)
	{
		if (word->redir == IN)
		{
			*has_in = true;
			if (word->next)
			{
				if (access(word->next->word, F_OK) < 0)
				{
					no_file_or_directory(word->next->word, data);
					return (-1);
				}
			}
		}
		word = word->next;
	}
	return (0);
}

static int	get_fd(t_word *word, int *fd, t_data *data)
{
	while (word)
	{
		if (word->redir == IN)
		{
			if (word->next)
			{
				if (*fd)
					close(*fd);
				*fd = open(word->next->word, O_RDONLY);
				if (*fd < 0)
				{
					print_fd(STDERR_FILENO, "minishell: %s: ", word->next->word);
					perror("");
					data->exit_status = 1;
					return (-1);
				}
			}
		}
		word = word->next;
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
