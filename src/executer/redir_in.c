/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:24:51 by carlaugu          #+#    #+#             */
/*   Updated: 2025/04/16 15:25:09 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execute.h"

int	check_file_exists(t_word *word, bool *has_in)
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
					perror ("minishell: ");
					return (-1);
				}
			}
		}
		word = word->next;
	}
	return (0);
}

int	get_fd(t_word *word, int *fd)
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
					perror ("minishell :");
					return (-1);
				}
			}
		}
		word = word->next;
	}
	return (0);
}

int	redir_in(t_word *word)
{
	int	fd;
	bool	has_in;

	has_in = false;
	fd = 0;
	if (check_file_exists(word->next, &has_in) == -1)
		return (-1);
	if (has_in)
	{
		if (get_fd(word->next, &fd) == -1)
			return (-1);
		redirect_stdin(&fd, 0);
	}
	return (0);
}
