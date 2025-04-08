/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:54:48 by tchow-so          #+#    #+#             */
/*   Updated: 2025/04/08 11:28:33 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/builtins.h"
#include "../../include/execve.h"
#include "../../include/expand.h"
#include "../../include/errors.h"

static int	is_builtin_cmd(t_tree_node **node);
static void exec_builtin_cmd(t_data *data, t_tree_node **node, int *i);

void	ast_depth_search(t_data *data, t_tree_node **node, int *i)
{
	t_tree_node	*tmp;

	tmp = *node;
	if (tmp->left)
		ast_depth_search(data, &tmp->left, i);
	if (exec_ast(data, node, i) == -1) //check if cmd or condition / pipe
		return ;
	if (tmp->right)
		ast_depth_search(data, &tmp->right, i);
}

int	exec_ast(t_data *data, t_tree_node **node, int *i)
{
	//expand variables that need expansion
	//remove quotes
	if (is_builtin_cmd(node))
	{
		if (analyze_args((*node)->word->next, data) == -1) //expander (?)
			return (-1);
		exec_builtin_cmd(data, node, i);
	}
	else
		exec(data, (*node)->word);
	//check exit codes for conditional execution
	return (0);
}

static int	is_builtin_cmd(t_tree_node **node)
{
	if (!ft_strcmp((*node)->word->word, "echo")
		|| !ft_strcmp((*node)->word->word, "cd")
		|| !ft_strcmp((*node)->word->word, "pwd")
		|| !ft_strcmp((*node)->word->word ,"export")
		|| !ft_strcmp((*node)->word->word,"unset")
		|| !ft_strcmp((*node)->word->word,"env")
		|| !ft_strcmp((*node)->word->word, "exit"))
		return (1);
	else
		return (0);

}

static void exec_builtin_cmd(t_data *data, t_tree_node **node, int *i)
{
	if (!ft_strcmp((*node)->word->word, "echo"))
		echo((*node)->word, data);
	else if (!ft_strcmp((*node)->word->word, "cd")) //TODO: check cd verification (cd_error)
		cd((*node)->word, data);
	else if (!ft_strcmp((*node)->word->word, "pwd"))
		pwd(data);	
	else if (!ft_strcmp((*node)->word->word ,"export"))
		export(data, (*node)->word);
	else if (!ft_strcmp((*node)->word->word,"unset"))
		unset(data, (*node)->word->next);
	else if (!ft_strcmp((*node)->word->word,"env"))
		env_cmd(data->env, data);
	else if (!ft_strcmp((*node)->word->word, "exit"))
		check_exit_args(data, node, i);
}

//conditional_exec