/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 10:25:40 by tchow-so          #+#    #+#             */
/*   Updated: 2025/04/17 15:41:11 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/execute.h"
#include "../../include/utils.h"
#include "../../include/errors.h"

//static int	get_proc_id(int *id);

/* A pipe is a connection between two processes, that allows one-way 
communication: fd[0] for the read end, fd[1] for the write end of the pipe*/
int	redir_pipe(t_data *data, t_word *word)
{
	int	old_stdin;
	int	old_stdout;
	int	fd[2];
	int	id;

	(void)data;
	(void)word;
	old_stdin = dup(STDIN_FILENO);
	old_stdout = dup(STDOUT_FILENO);
	//dup2(STDIN_FILENO, old_stdout);
	//dup2(STDOUT_FILENO, old_stdin);
	if (pipe(fd) == -1)
	{
		ft_putstr_fd("Minishell: pipe error\n", STDERR_FILENO);
		return (-1);
	}
	if (get_proc_id(&id) == -1)
		return (-1);
	if (id == 0)
	{
		close(fd[0]); //read
		dup2(fd[1], STDOUT_FILENO);
		//close(fd[1]); //write
	}
	else
	{
		close(fd[1]); //write
		dup2(fd[0], STDIN_FILENO);
		//close(fd[0]); //read
	}
	return (0);
}

/*static int	get_proc_id(int *id)
{
	*id = fork();
	if (*id == -1)
	{
		ft_putstr_fd("Minishell: fork error\n", STDERR_FILENO);
		return (-1);
	}
	return (0);
}*/

/*static void	()
{
	;
}*/
