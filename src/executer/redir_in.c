/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:24:51 by carlaugu          #+#    #+#             */
/*   Updated: 2025/04/17 11:05:06 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execute.h"
#include "../../include/errors.h"
#include "../../include/utils.h"

int	check_file_exists(t_word *word, bool *has_in, t_data *data);
int	get_fd(t_word *word, int *fd, t_data *data);
void	redirect_stdin(int *fd, int i);

int	redir_in(t_word *word, t_data *data)
{
	int	fd;

	if (!word->next)
		return (0);
	fd = 0;
	if (get_fd(word->next, &fd, data) == -1)
			return (-1);
	redirect_stdin(&fd, 0);
	return (0);
}

int	get_fd(t_word *word, int *fd, t_data *data)
{
	while (word)
	{
		if (word->redir == IN)
		{
			if (word->next)
			{
				if (*fd)
				{
					if (close(*fd) < 0)
					{
						perror("");
						data->exit_status = 1;
						return (-1);
					}

				}
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

void	redirect_stdin(int *fd, int i)
{
	if (dup2(fd[i], STDIN_FILENO) == -1)
	{
		perror("minishell: dup2");
		return ;
	}
}