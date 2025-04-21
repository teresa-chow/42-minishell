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

static int	create_pipe(t_data *data, t_tree_node **node, int *i);
static int	write_to_pipe(t_data *data, t_tree_node **node, int *i, int *fd);
static int	read_from_pipe(t_data *data, t_tree_node **node, int *i, int *fd);
//static int	get_proc_id(int *id);

void	ast_handle_pipe(t_data *data, t_tree_node **node, int *i)
{
	int	id;
	//int	old_stdin;
	//int	old_stdout;
	
	//old_stdin = dup(STDIN_FILENO);
	//old_stdout = dup(STDOUT_FILENO);
	create_pipe(data, node, i);
	if (is_builtin_cmd(node))
	{
		id = fork();
		if (id == -1)
		{
			ft_putstr_fd("Minishell: fork error\n", STDERR_FILENO);
			return (-1);
		}
	}
	//reset_old_in_out(old_stdin, old_stdout);
}

static int	create_pipe(t_data *data, t_tree_node **node, int *i)
{
	int	fd[2];

	if (pipe(fd) == -1)
	{
		ft_putstr_fd("Minishell: pipe error\n", STDERR_FILENO);
		return (-1);
	}
	return (0);
}

static int	write_to_pipe(t_data *data, t_tree_node **node, int *i, int *fd)
{
	int	id;

	if (is_builtin_cmd(node))
	{
		id = fork();
		if (get_proc_id(&id) == -1)
			return (-1);
		if (id == 0)
		{
			close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);
			ast_depth_search(data, &(*node)->left, i);
			close(fd[1]);
		}
		else
		{}
	}
	else
	{
		close(fd[1]);
		waitpid(id, &status, 0);
		close(fd[0]);
	}*/
	return (0);
}

static int	read_from_pipe(t_data *data, t_tree_node **node, int *i, int *fd)
{
//	int	id;

	/*id = fork();
	if (get_proc_id(&id) == -1)
		return (-1);
	if (id == 0)
	{*/
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		ast_depth_search(data, &(*node)->right, i);
		close(fd[0]);
	/*}
	else
	{
		close(fd[0]);
		waitpid(id, &status, 0);
		close(fd[1]);
	}*/
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
