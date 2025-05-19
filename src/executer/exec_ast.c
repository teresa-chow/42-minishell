/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:00:09 by tchow-so          #+#    #+#             */
/*   Updated: 2025/05/19 13:53:39 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/expand.h"
#include "../../include/execute.h"
#include "../../include/builtins.h"
#include "../../include/execve.h"
#include "../../include/errors.h"

static void	conditional_exec(t_data *data, t_tree_node **node, bool pipeline,
				t_tree_node *tmp);

void	ast_depth_search(t_data *data, t_tree_node **node, bool pipeline)
{
	t_tree_node	*tmp;

	tmp = *node;
	if (!tmp || data->status == 0)
		return ;
	if (tmp->type == GROUP)
	{
		ast_handle_group(data, node);
		return ;
	}
	if (tmp->type == PIPE)
	{
		ast_handle_pipeline(data, node);
		return ;
	}
	if (tmp->left)
		ast_depth_search(data, &tmp->left, pipeline);
	conditional_exec(data, node, pipeline, tmp);
}

static void	conditional_exec(t_data *data, t_tree_node **node, bool pipeline,
	t_tree_node *tmp)
{
	if (exec_ast(data, node, pipeline) != -1)
	{
		if (tmp->right)
			ast_depth_search(data, &tmp->right, pipeline);
	}
	else if (tmp->right && tmp->right->right)
	{
		//if (tmp->right->right
		//	&& (tmp->right->right->type == AND || tmp->right->right->type == OR))
		ast_depth_search(data, &tmp->right->right, pipeline);
	}
}

int	exec_ast(t_data *data, t_tree_node **node, bool pipeline)
{
	if ((*node)->type == AND)
	{
		if (data->exit_status != 0)
			return (-1);
	}
	else if ((*node)->type == OR)
	{
		if (data->exit_status == 0)
			return (-1);
	}
	else if ((*node)->type == CMD)
	{
		if (pipeline && (*node)->fd_in != -1)
			dup2((*node)->fd_in, STDIN_FILENO);
		if (exec_ast_cmd(data, node, pipeline) == -1)
		{
			reset_old_in_out(data, *node);
			return (-1);
		}
	}
	return (0);
}

int	exec_ast_cmd(t_data *data, t_tree_node **node, bool pipeline)
{
	save_old_in_out(data);
	if (handle_tokens((*node)->word, data, node) == -1)
		return (-1);
	if (handle_wildcard((*node)->word, data) == -1)
		return (-1);
	if (process_remove_quotes((*node)->word, data) == -1)
		return (-1);
	if (redir_check(*node, data) != 0)
		return (-1);
	if (is_builtin_cmd((*node)->word))
		exec_builtin_cmd(data, (*node)->word);
	else
		exec_child(data, pipeline, *node);
	reset_old_in_out(data, *node);
	return (0);
}
