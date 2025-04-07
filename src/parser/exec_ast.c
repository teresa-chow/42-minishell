/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:54:48 by tchow-so          #+#    #+#             */
/*   Updated: 2025/04/07 16:19:15 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/builtins.h"
#include "../../include/execve.h"
#include "../../include/expand.h"
#include "../../include/errors.h"

static int is_builtin_cmd(t_data *data, t_tree_node **node, int *i);

void	ast_depth_search(t_data *data, t_tree_node **node, int *i)
{
	t_tree_node	*tmp;

	tmp = *node;
	if (tmp->left)
		ast_depth_search(data, &tmp->left, i);
	exec_ast(data, node, i);
	if (tmp->right)
		ast_depth_search(data, &tmp->right, i);
}

void	exec_ast(t_data *data, t_tree_node **node, int *i)
{
	//expand variables that need expansion
	//remove quotes
	if (!is_builtin_cmd(data,node, i))
		exec(data, (*node)->word);
	//check exit codes for conditional execution
}

static int is_builtin_cmd(t_data *data, t_tree_node **node, int *i)
{
	int	is_bi;

	(void)i;
	is_bi = 1;
	if (ft_strcmp((*node)->word->word, "echo") == 0)
		echo((*node)->word, data);
	else if (ft_strcmp((*node)->word->word, "cd") == 0) //TODO: check cd verification (cd_error)
		cd((*node)->word, data);
	else if (ft_strcmp((*node)->word->word, "pwd") == 0)
		pwd(data);	
	else if (ft_strcmp((*node)->word->word ,"export") == 0)
		export(data, (*node)->word);
	else if (ft_strcmp((*node)->word->word,"unset") == 0)
		unset(data, (*node)->word->next);
	else if (ft_strcmp((*node)->word->word,"env") == 0)
		env_cmd(data->env, data);
	//else if (!ft_strcmp((*node)->word->word, "exit"))
		//check_exit_args(data, node, i);
	else
		is_bi = 0;
	return (is_bi);
}
