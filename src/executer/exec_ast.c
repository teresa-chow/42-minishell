/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:00:09 by tchow-so          #+#    #+#             */
/*   Updated: 2025/04/29 10:08:34 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/expand.h"
#include "../../include/execute.h"
#include "../../include/builtins.h"
#include "../../include/execve.h"
#include "../../include/errors.h"

void	ast_depth_search(t_data *data, t_tree_node **node, bool pipeline)
{
	t_tree_node	*tmp;

	tmp = *node;
	if (!tmp || data->status == 0)
		return ;
	if (tmp->type == PIPE)
	{
		ast_handle_pipeline(data, node);
		return ;
	}
	if (tmp->left)
		ast_depth_search(data, &tmp->left, pipeline);
	if (exec_ast(data, node, pipeline) == -1)
		return ; //check early return
	if (tmp->right)
		ast_depth_search(data, &tmp->right, pipeline);
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
		if (exec_ast_cmd(data, node, pipeline) == -1)
			return (-1);
	}
	return (0);
}

int	exec_ast_cmd(t_data *data, t_tree_node **node, bool pipeline)
{
	int	old_stdin;
	int	old_stdout;
	
	save_old_in_out(&old_stdin, &old_stdout);
	redir_heredoc(data, (*node)->word);
	if (handle_tokens((*node)->word, data, node) == -1)
		return (-1);
	if (handle_wildcard((*node)->word, data) == -1)
		return (-1);
	if (process_remove_quotes((*node)->word) == -1)
		return (-1);
	if (redir_in_out_check((*node)->word, data) != 0)
		return (-1);
	if (is_builtin_cmd((*node)->word))
		exec_builtin_cmd(data, (*node)->word);
	else
		exec_child(data, (*node)->word, pipeline);
	reset_old_in_out(old_stdin, old_stdout);
	return (0);
}

int is_builtin_cmd(t_word *word)
{
	t_word	*tmp;

	tmp = word;
	while (tmp && tmp->redir != NONE)
		tmp = tmp->next->next;
	if (!tmp)
		return (0);
	if (!ft_strcmp(tmp->word, "echo")
		|| !ft_strcmp(tmp->word, "cd")
		|| !ft_strcmp(tmp->word, "pwd")
		|| !ft_strcmp(tmp->word, "export")
		|| !ft_strcmp(tmp->word, "unset")
		|| !ft_strcmp(tmp->word, "env")
		|| !ft_strcmp(tmp->word, "exit"))
		return (1);
	return (0);
}

void exec_builtin_cmd(t_data *data, t_word *word)
{
	t_word	*tmp;

	tmp = word;
	while (tmp->redir != NONE)
		tmp = tmp->next->next;
	if (!ft_strcmp(tmp->word, "echo"))
		echo(tmp, data);
	else if (!ft_strcmp(tmp->word, "cd"))
	{
		if (!cd_arg_check(tmp, data))
			return ;
		cd(tmp, data);
	}
	else if (!ft_strcmp(tmp->word, "pwd"))
		pwd(data);
	else if (!ft_strcmp(tmp->word, "export"))
		export(data, tmp);
	else if (!ft_strcmp(tmp->word, "unset"))
		unset(data, tmp->next);
	else if (!ft_strcmp(tmp->word, "env"))
		env_cmd(data->env, data);
	else if (!ft_strcmp(tmp->word, "exit"))
		exit_cmd(data, tmp);
}
