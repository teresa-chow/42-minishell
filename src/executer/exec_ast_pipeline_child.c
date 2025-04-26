/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast_pipeline_child.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 21:58:26 by tchow-so          #+#    #+#             */
/*   Updated: 2025/04/26 23:41:26 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/execute.h"
#include "../../include/builtins.h"
#include "../../include/execve.h"
#include "../../include/errors.h"

void	exec_pipeline_child(t_pipeline pipeline, t_data *data,
	t_word *word, int *i, int count) //refactor int *i
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (count < pipeline.n_pipes - 1)
		{
			close(pipeline.fd[count][0]);
			dup2(pipeline.fd[count][1], STDOUT_FILENO);
			close(pipeline.fd[count][1]);
		}
		if (count > 0)
		{
			close(pipeline.fd[count - 1][1]);
			dup2(pipeline.fd[count - 1][0], STDIN_FILENO);
			close(pipeline.fd[count - 1][0]);
		}
		if (is_builtin_cmd(word))
			exec_builtin_cmd(data, word, i);
		else
			exec(data, word); //check double fork
		exit(1);
	}
}