/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:00:09 by tchow-so          #+#    #+#             */
/*   Updated: 2025/04/23 16:22:04 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/expand.h"
#include "../../include/execute.h"
#include "../../include/builtins.h"
#include "../../include/execve.h"
#include "../../include/errors.h"

static int	exec_ast(t_data *data, t_tree_node **node, int *i);
static void	exec_builtin_cmd(t_data *data, t_tree_node **node, int *i);

void	ast_depth_search(t_data *data, t_tree_node **node, int *i)
{
	t_tree_node	*tmp;

	if (!*node)
		return ;
	tmp = *node;
	if (tmp->type == PIPE) //segfault
	{
		ast_handle_pipe(data, node, i);
		return ;
	}
	if (tmp->left)
		ast_depth_search(data, &tmp->left, i);
	if (exec_ast(data, node, i) == -1)
		return ; //check early return
	if (tmp->right)
		ast_depth_search(data, &tmp->right, i);
}

static int	exec_ast(t_data *data, t_tree_node **node, int *i)
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
		if (exec_ast_cmd(data, node, i) == -1)
			return (-1);
	}
	return (0);
}

int	exec_ast_cmd(t_data *data, t_tree_node **node, int *i)
{
	int	old_stdin;
	int	old_stdout;
	
	save_old_in_out(&old_stdin, &old_stdout);
	//redir_heredoc(data, (*node)->word);
	if (handle_tokens((*node)->word, data, node) == -1)
		return (-1);
	if (handle_wildcard((*node)->word, data) == -1)
		return (-1);
	if (remove_quotes((*node)->word) == -1)
		return (-1);
	if (redir_in_out_check((*node)->word, data) != 0)
		return (-1);
	if (is_builtin_cmd(node))
		exec_builtin_cmd(data, node, i);
	else
		exec(data, (*node)->word);
	reset_old_in_out(old_stdin, old_stdout);
	return (0);
}

int is_builtin_cmd(t_tree_node **node)
{
	t_word	*tmp;

	if (!*node)
		return (-1);
	tmp = (*node)->word;
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

static void exec_builtin_cmd(t_data *data, t_tree_node **node, int *i)
{
	t_word	*tmp;

	tmp = (*node)->word;
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
		exit_cmd(data, tmp, i);
}
