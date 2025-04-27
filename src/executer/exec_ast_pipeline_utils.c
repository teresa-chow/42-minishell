/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast_pipeline_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:39:33 by tchow-so          #+#    #+#             */
/*   Updated: 2025/04/27 10:43:03 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/execute.h"
#include "../../include/builtins.h"
#include "../../include/execve.h"
#include "../../include/errors.h"

static void	get_pipeline_cmds(t_pipeline *pipeline, t_tree_node **node);

void	traverse_pipeline(t_pipeline *pipeline, t_tree_node **node)
{
	t_tree_node	*tmp;

	if (!*node)
		return ;
	tmp = *node;
	if (tmp->left)
		traverse_pipeline(pipeline, &tmp->left);
	if (tmp->type == PIPE)
		pipeline->n_pipes++;
	else if (tmp->type == CMD)
		get_pipeline_cmds(pipeline, node);
	if (tmp->right)
		traverse_pipeline(pipeline, &tmp->right);
}

static void	get_pipeline_cmds(t_pipeline *pipeline, t_tree_node **node)
{
	t_word_lst	*tmp;
	t_word_lst	*new;

	new = NULL;
	if (!pipeline->cmd_lst)
	{
		pipeline->cmd_lst = ft_calloc(1, sizeof(t_word_lst));
		pipeline->cmd_lst->word = (*node)->word;
	}
	else
	{
		tmp = pipeline->cmd_lst;
		new = ft_calloc(1, sizeof(t_word_lst));
		new->word = (*node)->word;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	exec_pipeline_child(t_pipeline pipeline, t_data *data,
	t_word *word, int *i, int count) //refactor int *i
{
	pipeline.pid[count] = fork();
	if (pipeline.pid[count] == 0)
	{
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
		if (is_builtin_cmd(word))
			exec_builtin_cmd(data, word, i);
		else
			exec(data, word);
		exit(data->exit_status);
	}
}
