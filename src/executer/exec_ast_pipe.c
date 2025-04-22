/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 11:24:52 by tchow-so          #+#    #+#             */
/*   Updated: 2025/04/21 17:02:11 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/execute.h"
#include "../../include/builtins.h"
#include "../../include/execve.h"
#include "../../include/errors.h"

void	ast_handle_pipe(t_data *data, t_tree_node **node, int *i)
{
	int	id;
	int	fd[2];
	int	status_w = 0;
	int	status_r = 0;
	int	old_stdin;
	int	old_stdout;
	
	old_stdin = dup(STDIN_FILENO);
	old_stdout = dup(STDOUT_FILENO);
	if (pipe(fd) == -1)
	{
		ft_putstr_fd("Minishell: pipe error\n", STDERR_FILENO);
		return ;
	};
	if (is_builtin_cmd(&(*node)->left))
	{
		id = fork();
		if (id == -1)
		{
			ft_putstr_fd("Minishell: fork error\n", STDERR_FILENO);
			return ;
		}
		if (id == 0)
		{
			close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);
			exec_ast_cmd(data, &(*node)->left, i);
			close(fd[1]);
		}
		else
			waitpid(id, &status_w, 0);
	}
	else
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		ast_depth_search(data, &(*node)->left, i);
		close(fd[1]);
	}
	if (is_builtin_cmd(&(*node)->right))
	{
		id = fork();
		if (id == -1)
		{
			ft_putstr_fd("Minishell: fork error\n", STDERR_FILENO);
			return ;
		}
		if (id == 0)
		{
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
			exec_ast_cmd(data, &(*node)->right, i);
			close(fd[0]);
		}
		else
			waitpid(id, &status_r, 0);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		ast_depth_search(data, &(*node)->right, i);
		close(fd[0]);
	}
	close(fd[1]);
	close(fd[0]);
	reset_old_in_out(old_stdin, old_stdout);
}

