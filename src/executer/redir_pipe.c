/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 10:25:40 by tchow-so          #+#    #+#             */
/*   Updated: 2025/04/17 11:04:03 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/execute.h"
#include "../../include/utils.h"
#include "../../include/errors.h"

/* A pipe is a connection between two processes, that allows one-way communication only*/
int	redir_pipe(t_data *data, t_word *word)
{
	int	fd[2];
	int	id;

	if (alloc_read_write_fd(&fd) == -1)
		return (-1);
	if (get_proc_id(&id) == -1)
		return (-1);
}
static int	alloc_read_write_fd(int	*fd)
{
	if (pipe(*fd) == -1)
	{
		ft_putstr_fd("Minishell: pipe error\n", STDERR_FILENO);
		return (-1);
	}
	return (0);
}

static int	get_proc_id(int *id)
{
	*id = fork();
	if (*id == -1)
	{
		ft_putstr_fd("Minishell: fork error\n", STDERR_FILENO);
		return (-1);
	}
	return (0);
}
