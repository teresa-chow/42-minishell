/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:00:09 by tchow-so          #+#    #+#             */
/*   Updated: 2025/04/21 16:40:48 by tchow-so         ###   ########.fr       */
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

	tmp = *node;
	if (tmp->type == PIPE)
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
	if (redir_in_out_check((*node)->word, data) != 0)
		return (-1);
	if (is_builtin_cmd(node))
		exec_builtin_cmd(data, node, i);
	else if ((*node)->word->redir == NONE)
		exec(data, (*node)->word);
	reset_old_in_out(old_stdin, old_stdout);
	return (0);
}

int is_builtin_cmd(t_tree_node **node)
{
	if (!ft_strcmp((*node)->word->word, "echo")
		|| !ft_strcmp((*node)->word->word, "cd")
		|| !ft_strcmp((*node)->word->word, "pwd")
		|| !ft_strcmp((*node)->word->word, "export")
		|| !ft_strcmp((*node)->word->word, "unset")
		|| !ft_strcmp((*node)->word->word, "env")
		|| !ft_strcmp((*node)->word->word, "exit"))
		return (1);
	return (0);
}

static void exec_builtin_cmd(t_data *data, t_tree_node **node, int *i)
{
	if (!ft_strcmp((*node)->word->word, "echo"))
		echo((*node)->word, data);
	else if (!ft_strcmp((*node)->word->word, "cd"))
	{
		if ((*node)->word->next	&& (*node)->word->next->next
		&& (*node)->word->next->next->redir == NONE)
		{
			cd_error(NULL, data, 0);
			return ;
		}
		cd((*node)->word, data);
	}
	else if (!ft_strcmp((*node)->word->word, "pwd"))
		pwd(data);
	else if (!ft_strcmp((*node)->word->word, "export"))
		export(data, (*node)->word);
	else if (!ft_strcmp((*node)->word->word, "unset"))
		unset(data, (*node)->word->next);
	else if (!ft_strcmp((*node)->word->word, "env"))
		env_cmd(data->env, data);
	else if (!ft_strcmp((*node)->word->word, "exit"))
		exit_cmd(data, node, i);
}
