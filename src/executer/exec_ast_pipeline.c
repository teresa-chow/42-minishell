/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast_pipeline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 11:24:52 by tchow-so          #+#    #+#             */
/*   Updated: 2025/04/27 18:26:58 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/execute.h"
#include "../../include/builtins.h"
#include "../../include/execve.h"
#include "../../include/errors.h"

static int		create_pipeline(t_pipeline *pipeline, t_tree_node **node);
static int		create_pipe(int	fd[2]);
static void		exec_pipeline(t_pipeline pipeline, t_data *data);
static void		wait_children(t_data *data, t_pipeline *pipeline);

void	ast_handle_pipeline(t_data *data, t_tree_node **node)
{
	t_pipeline	pipeline;

	ft_bzero(&pipeline, sizeof(t_pipeline));
	create_pipeline(&pipeline, node);
	exec_pipeline(pipeline, data);
	wait_children(data, &pipeline);
	//free_pipeline
}

static int	create_pipeline(t_pipeline *pipeline, t_tree_node **node)
{
	int	count;

	count = 0;
	traverse_pipeline(pipeline, node);
	pipeline->fd = ft_calloc(pipeline->n_pipes, sizeof(int *));
	pipeline->pid = ft_calloc(pipeline->n_pipes + 1, sizeof(pid_t));
	while (count < pipeline->n_pipes)
	{
		pipeline->fd[count] = ft_calloc(2, sizeof(int));
		if (create_pipe(pipeline->fd[count]) == -1)
			return (-1);
		count++;
	}
	return (0);
}

/* Obs.: fd[0] is set up for reading, fd[1] is set up for writing */
static int	create_pipe(int	fd[2])
{
	if (pipe(fd) == -1)
	{
		ft_putstr_fd("Minishell: pipe error\n", STDERR_FILENO);
		return (-1);
	}
	return (0);
}

static void	exec_pipeline(t_pipeline pipeline, t_data *data)
{
	t_word_lst	*tmp;
	int	count;

	count = 0;
	tmp = pipeline.cmd_lst;
	while (tmp)
	{
		if (count > 0)
		{
			close(pipeline.fd[count - 1][0]);
			close(pipeline.fd[count - 1][1]);
		}
		exec_pipeline_child(pipeline, data, tmp->word, count);
		tmp = tmp->next;
		count++;
	}
}

static void	wait_children(t_data *data, t_pipeline *pipeline)
{
	int	count;
	int	status;

	count = 0;
	status = 0;
	while (count <= pipeline->n_pipes)
	{
		waitpid(pipeline->pid[count], &status, 0);
		count++;
	}
	data->exit_status = WEXITSTATUS(status);
}
