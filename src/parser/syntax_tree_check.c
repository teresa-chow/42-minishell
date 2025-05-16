/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_tree_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:53:28 by tchow-so          #+#    #+#             */
/*   Updated: 2025/05/16 15:17:30 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/errors.h"
#include "../../include/utils.h"

/*static int	check_ast_syntax(t_tree_node **node);

int	check_ast(t_tree_node **root, t_data *data)
{
	if ((*root)->word)
	{
		if (!check_ast_syntax())
		{
			free_ast(root); //root is set to NULL
			data->exit_status = ERR_BI;
			return (ERR_BI);
		}
	}
}

static int	check_ast_syntax(t_tree_node **node)
{
	int	ret;

	ret = 0;
	if (!*node)
		return (ret);
	if ((*node)->left)
		check_ast_syntax(&(*node)->left);
	check_neighbors(*node);
	return (ret);
	if ((*node)->right)
		check_ast_syntax(&(*node)->right);
}

static int	check_neighbors(t_tree_node *node)
{
	if (node->type == GROUP)
	{
		if (node->left->type != AND && node->left->type != OR)
			return (ERR_BI);
	}
	return (0);
}*/