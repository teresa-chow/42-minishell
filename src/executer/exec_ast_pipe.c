/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 11:24:52 by tchow-so          #+#    #+#             */
/*   Updated: 2025/04/22 09:32:45 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/execute.h"
#include "../../include/builtins.h"
#include "../../include/execve.h"
#include "../../include/errors.h"

void	ast_handle_pipe(t_data *data, t_tree_node **node, int *i)
{
	int	pid_w;
	int	pid_r;
	int	fd[2];

	if (pipe(fd) == -1)
	{
		ft_putstr_fd("Minishell: pipe error\n", STDERR_FILENO);
		return ;
	};
	if (is_builtin_cmd(&(*node)->left))
	{
		pid_w = fork();
		if (pid_w == -1)
		{
			ft_putstr_fd("Minishell: fork error\n", STDERR_FILENO);
			return ;
		}
		if (pid_w == 0)
		{
			close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
			exec_ast_cmd(data, &(*node)->left, i);
		}
	}
	else
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		ast_depth_search(data, &(*node)->left, i);
	}
	if (is_builtin_cmd(&(*node)->right))
	{
		pid_r = fork();
		if (pid_r == -1)
		{
			ft_putstr_fd("Minishell: fork error\n", STDERR_FILENO);
			return ;
		}
		if (pid_r == 0)
		{
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			exec_ast_cmd(data, &(*node)->right, i);
		}
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		ast_depth_search(data, &(*node)->right, i);
	}
	if (pid_w != 0 && pid_r != 0)
	{
		waitpid(pid_w, NULL, 0);
		waitpid(pid_r, NULL, 0);
		close(fd[1]);
		close(fd[0]);
	}
}

