/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 11:24:52 by tchow-so          #+#    #+#             */
/*   Updated: 2025/04/22 22:35:49 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/execute.h"
#include "../../include/builtins.h"
#include "../../include/execve.h"
#include "../../include/errors.h"

static int	create_pipe(int	fd[2]);
static void	pipe_output(t_data *data, t_tree_node **node_right, int *i,
	int fd[2]);
static void	pipe_input(t_data *data, t_tree_node **node_right, int *i,
	int fd[2]);

/* Obs.: fd[0] is set up for reading, fd[1] is set up for writing */
void	ast_handle_pipe(t_data *data, t_tree_node **node, int *i)
{
	int	fd[2];

	if (create_pipe(&fd[2]) == -1)
		return ;
	pipe_output(data, &(*node)->right, i, &fd[2]);
	pipe_input(data, &(*node)->left, i, &fd[2]);
	close(fd[1]);
	close(fd[0]);
}

static int	create_pipe(int	fd[2])
{
	if (pipe(fd) == -1)
	{
		ft_putstr_fd("Minishell: pipe error\n", STDERR_FILENO);
		return (-1);
	}
	return (0);
}

static void	pipe_output(t_data *data, t_tree_node **node_right, int *i, int fd[2])
{
	int	id;

	if (is_builtin_cmd(node_right))
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
			exec_ast_cmd(data, node_right, i);
			close(fd[0]);
		}
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		ast_depth_search(data, node_right, i);
		close(fd[0]);
	}
}

static void	pipe_input(t_data *data, t_tree_node **node_left, int *i, int fd[2])
{
	int	id;

	if (is_builtin_cmd(node_left))
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
			dup2(fd[1], STDIN_FILENO);
			exec_ast_cmd(data, node_left, i);
			close(fd[1]);
		}
	}
	else
	{
		close(fd[0]);
		dup2(fd[1], STDIN_FILENO);
		ast_depth_search(data, node_left, i);
		close(fd[1]);
	}
}
