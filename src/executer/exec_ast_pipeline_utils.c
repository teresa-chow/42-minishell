/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast_pipeline_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:39:33 by tchow-so          #+#    #+#             */
/*   Updated: 2025/04/30 23:41:42 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/execute.h"
#include "../../include/builtins.h"
#include "../../include/execve.h"
#include "../../include/errors.h"

static void	get_pipeline_cmds(t_pipeline *pipeline, t_tree_node **node);
static void	close_pipes_child(t_pipeline pipeline, int count);
static void	free_child(t_pipeline pipeline, t_data *data);
static	int	find_heredoc_fd(t_word *word);

void	traverse_pipeline(t_data *data, t_pipeline *pipeline,
			t_tree_node **node)
{
	t_tree_node	*tmp;

	(void)data;
	if (!*node)
		return ;
	tmp = *node;
	if (tmp->left)
		traverse_pipeline(data, pipeline, &tmp->left);
	if (tmp->type == PIPE)
		pipeline->n_pipes++;
	else if (tmp->type == CMD)
		get_pipeline_cmds(pipeline, node);
	if (tmp->right)
		traverse_pipeline(data, pipeline, &tmp->right);
}

static void	get_pipeline_cmds(t_pipeline *pipeline, t_tree_node **node)
{
	t_tree_node	*tmp;
	t_tree_node	*new;

	new = NULL;
	if (!pipeline->cmd_lst)
	{
		pipeline->cmd_lst = ft_calloc(1, sizeof(t_tree_node));
		pipeline->cmd_lst->word = (*node)->word;
	}
	else
	{
		tmp = pipeline->cmd_lst;
		new = ft_calloc(1, sizeof(t_tree_node));
		new->word = (*node)->word;
		while (tmp->left)
			tmp = tmp->left;
		tmp->left = new;
	}
}

void	exec_pipeline_child(t_pipeline pipeline, t_data *data,
	t_tree_node *node, int count)
{
	int	heredoc_fd;

	heredoc_fd = 0;
	pipeline.pid[count] = fork();
	if (pipeline.pid[count] == 0)
	{
		heredoc_fd = find_heredoc_fd(node->word);
		signal(SIGINT, SIG_DFL);
		close_pipes_child(pipeline, count);
		if (count < pipeline.n_pipes)
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
		if (heredoc_fd)
			dup2(heredoc_fd, STDIN_FILENO);
		close_heredoc_fds(data, NULL);
		exec_ast(data, &node, 1);
		free_child(pipeline, data);
		exit(data->exit_status);
	}
}

static	int	find_heredoc_fd(t_word *word)
{
	int	i;

	i = 0;
	while (word)
	{
		if (word->in_fd)
			i = word->in_fd;
		word = word->next;
	}
	return (i);
}

static void	close_pipes_child(t_pipeline pipeline, int count)
{
	int	i;

	i = 0;
	while (i < pipeline.n_pipes)
	{
		if (i != count - 1)
			close(pipeline.fd[i][0]);
		if (i != count)
			close(pipeline.fd[i][1]);
		i++;
	}
}

static void	free_child(t_pipeline pipeline, t_data *data)
{
	free_pipeline(&pipeline);
	data->status = 0;
	reset_mem(data, &data->ast_root);
}
