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

static void	ast_depth_search(t_data *data, t_tree_node **node, int *i);

void	exec_ast(t_data *data, t_tree_node **root, int *i)
{
	ast_depth_search(data, root, i);
	//traverse ast (LIFO, depth first search, left-root-right)
	//expand variables that need expansion
	//remove quotes
	//execute cmd based on priority lvl (builtin or other)
	//check exit codes for conditional execution
}

static void	ast_depth_search(t_data *data, t_tree_node **node, int *i)
{
	//t_tree_node	*tmp;

	(void)data;
	(void)i;
	//tmp = node;
	//exec_ast(data, node, i);
	ft_printf("node word: %s\n", (*node)->word->word);
	/*if (tmp->left)
		ast_depth_search(data, tmp->left, i);
	if (tmp->right)
		ast_depth_search(data, tmp->right, i);*/
}

/*static int is_builtin_cmd(t_data *data, t_tree_node **node, int *i)
{
	int	is_bi;

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
	else if (!ft_strcmp((*node)->word->word, "exit"))
		check_exit_args(data, node, i);
	else
		is_bi = 0;
	return (is_bi);
}*/
/*
else
exec(data, (*node)->word);
*/