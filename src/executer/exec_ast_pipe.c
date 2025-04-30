/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 11:24:52 by tchow-so          #+#    #+#             */
/*   Updated: 2025/04/26 10:33:06 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/execute.h"
#include "../../include/builtins.h"
#include "../../include/execve.h"
#include "../../include/errors.h"

static int		create_pipe(int	fd[2]);
static pid_t	pipe_write(t_data *data, t_tree_node **node_right, int *i);
static pid_t	pipe_read(t_data *data, t_tree_node **node_right, int *i);

void	ast_handle_pipe(t_data *data, t_tree_node **node, int *i)
{
	pid_t	pid_left;
	pid_t	pid_right;

	pid_left = -1;
	pid_right = -1;
	if (!data->fd)
		data->fd = ft_calloc(data->n_pipes, sizeof(int *));
	data->fd[data->i] = ft_calloc(2, sizeof(int));
	if (create_pipe(data->fd[data->i]) == -1)
		return ;
	pid_left = pipe_write(data, &(*node)->left, i);
	pid_right = pipe_read(data, &(*node)->right, i);
	if (pid_right > 0)
		waitpid(pid_right, NULL, 0);
	if (pid_left > 0)
		waitpid(pid_left, NULL, 0);
	close(data->fd[data->i][1]);
	close(data->fd[data->i][0]);
	data->i++;
}

/* Obs.: fd[0] is set up for reading, fd[1] is set up for writing */
static int	create_pipe(int	fd[2])
{
	if (pipe(fd) == -1)
	{
		//free_fd_array();
		ft_putstr_fd("Minishell: pipe error\n", STDERR_FILENO);
		return (-1);
	}
	return (0);
}

static pid_t	pipe_write(t_data *data, t_tree_node **node_left, int *i)
{
	pid_t	id;

	id = -1;
	if ((*node_left)->type != CMD)
	{
		ast_depth_search(data, node_left, i);
		return (-1);
	}
	if (is_builtin_cmd(node_left))
	{
		id = fork();
		if (id == -1)
		{
			ft_putstr_fd("Minishell: fork error\n", STDERR_FILENO);
			return (-1);
		}
		if (id == 0)
		{
			close(data->fd[data->i][0]);
			dup2(data->fd[data->i][1], STDOUT_FILENO);
			close(data->fd[data->i][1]);
			exec_ast_cmd(data, node_left, i);
			exit(1);
		}
	}
	else
	{
		close(data->fd[data->i][0]); //closing in parent
		dup2(data->fd[data->i][1], STDOUT_FILENO);
		close(data->fd[data->i][1]); //closing in parent
		exec_ast_cmd(data, node_left, i); //execve runs process as child
	}
	return (id);
}

static pid_t	pipe_read(t_data *data, t_tree_node **node_right, int *i)
{
	pid_t	id;

	id = -1;
	if ((*node_right)->type != CMD)
	{
		ast_depth_search(data, node_right, i);
		return (-1);
	}
	if (is_builtin_cmd(node_right))
	{
		id = fork();
		if (id == -1)
		{
			ft_putstr_fd("Minishell: fork error\n", STDERR_FILENO);
			return (-1);
		}
		if (id == 0)
		{
			close(data->fd[data->i][1]);
			dup2(data->fd[data->i][0], STDIN_FILENO);
			close(data->fd[data->i][0]);
			exec_ast_cmd(data, node_right, i);
			exit(1);
		}
	}
	else
	{
		close(data->fd[data->i][1]); //closing in parent
		dup2(data->fd[data->i][0], STDIN_FILENO);
		close(data->fd[data->i][0]); //closing in parent
		exec_ast_cmd(data, node_right, i); //execve runs process as child
	}
	return (id);
}
