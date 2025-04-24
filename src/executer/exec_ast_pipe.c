/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 11:24:52 by tchow-so          #+#    #+#             */
/*   Updated: 2025/04/24 16:44:26 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/execute.h"
#include "../../include/builtins.h"
#include "../../include/execve.h"
#include "../../include/errors.h"

static int		create_pipe(int	fd[2]);
static pid_t	pipe_input(t_data *data, t_tree_node **node_right, int *i);
static pid_t	pipe_output(t_data *data, t_tree_node **node_right, int *i);

/* Obs.: fd[0] is set up for reading, fd[1] is set up for writing */

//lost fd reference in data (deleted, mus review)
//count pipes
//flatten pipeline
void	ast_handle_pipe(t_data *data, t_tree_node **node, int *i)
{
	pid_t	pid_left = -1;
	pid_t	pid_right = -1;

	data->fd_arr[data->i] = ft_calloc(2, sizeof(int));
		// if (!data->fd_arr[data->i])
	pid_left = pipe_input(data, &(*node)->left, i);
	pid_right = pipe_output(data, &(*node)->right, i);
	if (pid_right > 0)
		waitpid(pid_right, NULL, 0);
	if (pid_left > 0)
		waitpid(pid_left, NULL, 0);
	close(data->fd_arr[data->i][1]);
	close(data->fd_arr[data->i][0]);
	data->i--;
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

static pid_t	pipe_input(t_data *data, t_tree_node **node_left, int *i)
{
	pid_t	id;

	if (!*node_left)
		return (-1);
	if ((*node_left)->type != CMD)
	{
		ast_depth_search(data, node_left, i);
		return (-1);
	}
	if (create_pipe(data->fd_arr[data->i]) == -1)
		return (-1);
	id = fork();
	if (id == -1)
	{
		ft_putstr_fd("Minishell: fork error\n", STDERR_FILENO);
		return (-1);
	}
	if (id == 0)
	{
		close(data->fd_arr[data->i][0]);
		dup2(data->fd_arr[data->i][1], STDOUT_FILENO);
		close(data->fd_arr[data->i][1]);
		ast_depth_search(data, node_left, i);
		exit(1);
	}
	return (id);
}

static pid_t	pipe_output(t_data *data, t_tree_node **node_right, int *i)
{
	pid_t	id;

	if (!*node_right)
		return (-1);
	if ((*node_right)->type != CMD)
	{
		ast_depth_search(data, node_right, i);
		return (-1);
	}
	id = fork();
	if (id == -1)
	{
		ft_putstr_fd("Minishell: fork error\n", STDERR_FILENO);
		return (-1);
	}
	if (id == 0)
	{
		close(data->fd_arr[data->i][1]);
		dup2(data->fd_arr[data->i][0], STDIN_FILENO);
		close(data->fd_arr[data->i][0]);
		ast_depth_search(data, node_right, i);
		exit(1);
	}
	return (id);
}
