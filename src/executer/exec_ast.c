/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:54:48 by tchow-so          #+#    #+#             */
/*   Updated: 2025/04/10 09:34:07 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/builtins.h"
#include "../../include/execve.h"
#include "../../include/expand.h"
#include "../../include/errors.h"

static int	exec_ast(t_data *data, t_tree_node **node, int *i);
static int	exec_builtin_cmd(t_data *data, t_tree_node **node, int *i);

void	ast_depth_search(t_data *data, t_tree_node **node, int *i)
{
	t_tree_node	*tmp;

	tmp = *node;
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
		if (exec_ast_cmd(data, node, i) == -1) //check pipe
			return (-1);
	}
	return (0);
}

int	exec_ast_cmd(t_data *data, t_tree_node **node, int *i)
{
	//expand variables that need expansion
	//remove quotes
	if (handle_tokens((*node)->word, data) == -1) //rename: expander (?)
		return (-1);
	if (!exec_builtin_cmd(data, node, i))
		exec(data, (*node)->word);
	return (0);
}

static int exec_builtin_cmd(t_data *data, t_tree_node **node, int *i)
{
	int	bi;

	bi = 1;
	if (!ft_strcmp((*node)->word->word, "echo"))
		echo((*node)->word, data);
	else if (!ft_strcmp((*node)->word->word, "cd")) //check cd verification (at the bottom)
		cd((*node)->word, data);
	else if (!ft_strcmp((*node)->word->word, "pwd"))
		pwd(data);
	else if (!ft_strcmp((*node)->word->word, "export"))
		export(data, (*node)->word);
	else if (!ft_strcmp((*node)->word->word, "unset"))
		unset(data, (*node)->word->next);
	else if (!ft_strcmp((*node)->word->word, "env"))
		env_cmd(data->env, data);
	else if (!ft_strcmp((*node)->word->word, "exit"))
		check_exit_args(data, node, i);
	else
		bi = 0;
	return (bi);
}

/* Removed cd builtin check (redirections)
	if ((*node)->word->next && (*node)->word->next->next)
	{
			cd_error(NULL, data, 0);
			return ;
	}
*/