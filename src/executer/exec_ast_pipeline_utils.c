/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast_pipeline_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:39:33 by tchow-so          #+#    #+#             */
/*   Updated: 2025/05/08 13:35:05 by carlaugu         ###   ########.fr       */
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

void	traverse_pipeline(t_data *data, t_pipeline *pipeline,
			t_tree_node **node)
{
	t_tree_node	*tmp;

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
		pipeline->cmd_lst->fd_in = (*node)->fd_in;
	}
	else
	{
		tmp = pipeline->cmd_lst;
		new = ft_calloc(1, sizeof(t_tree_node));
		new->word = (*node)->word;
		new->fd_in = (*node)->fd_in;
		while (tmp->left)
			tmp = tmp->left;
		tmp->left = new;
	}
}

void	exec_pipeline_child(t_pipeline pipeline, t_data *data,
	t_tree_node *node, int count)
{
	pipeline.pid[count] = fork();
	if (pipeline.pid[count] == 0)
	{
		// printf("\n");
		signal(SIGINT, SIG_DFL);
		close_pipes_child(pipeline, count);
		if (count < pipeline.n_pipes)
		{
			// close(pipeline.fd[count][0]);
			// printf("--->fechei no child fd[%d][0] na exec_pipeline_child com %s %s %s\n", count, node->word->word, node->word->next->word, node->word->next->next->word);
			// printf("--->fechei no child fd[%d][1] na exec_pipeline_child com %s %s %s\n", count, node->word->word, node->word->next->word, node->word->next->next->word);
			dup2(pipeline.fd[count][1], STDOUT_FILENO);
			close(pipeline.fd[count][1]);
		}
		if (count > 0)
		{
			// close(pipeline.fd[count - 1][1]);
			// printf("--->fechei no child fd[%d][1] na exec_pipeline_child com %s %s %s\n", count - 1, node->word->word, node->word->next->word, node->word->next->next->word);
			dup2(pipeline.fd[count - 1][0], STDIN_FILENO);
			// close(pipeline.fd[count - 1][0]);
			// printf("--->fechei no child fd[%d][0] na exec_pipeline_child com %s %s %s\n", count - 1, node->word->word, node->word->next->word, node->word->next->next->word);
		}
		//if (node->fd_in != -1) //
		//	dup2(node->fd_in, STDIN_FILENO); //
		//close_heredoc_fds(data, NULL);
		exec_ast(data, &node, 1);
		free_child(pipeline, data);
		exit(data->exit_status);
	}
}

static void	close_pipes_child(t_pipeline pipeline, int count)
{
	int	i;

	i = 0;
	while (i > -1 && i < pipeline.n_pipes)
	{
		if (i != count - 1)
		{
			if (pipeline.fd[i][0] != -1)
			{
				close(pipeline.fd[i][0]);
				// printf("->fechei fd[%d][0] no child em close_pipes;\n", i);
			}
		}
		if (i != count)
		{
			if (pipeline.fd[i][1] != -1)
			{
				close(pipeline.fd[i][1]);	
				// printf("->fechei fd[%d][1] no child no child em close_piepes\n", i);
			}
		}
		i++;
	}
}

static void	free_child(t_pipeline pipeline, t_data *data)
{
	free_pipeline(&pipeline);
	data->status = 0;
	reset_mem(data, &data->ast_root);
}
