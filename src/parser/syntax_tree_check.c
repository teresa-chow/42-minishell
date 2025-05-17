/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_tree_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:30:33 by tchow-so          #+#    #+#             */
/*   Updated: 2025/05/17 11:45:13 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/errors.h"
#include "../../include/utils.h"

static int	check_neighbors(t_tree_node **node, t_data *data);

int check_syntax_tree(t_tree_node **root, t_data *data)
{
	if (!check_neighbors(root, data))
	{
		free_ast(root);
		return (0);
	}
	return (1);
}

static int	check_neighbors(t_tree_node **node, t_data *data)
{
	int	ret;

	ret = 1;
	if (!*node)
		return (ret);
	if ((*node)->left)
		ret = check_neighbors(&(*node)->left, data);
	if ((*node)->type == GROUP
		&& ((*node)->left->type == GROUP && !(*node)->right))
	{
		data->exit_status = ERR;
		ret = 0;
	}
	else if ((*node)->type == GROUP
		&& ((*node)->left->type != AND && (*node)->left->type != OR))
	{
		data->exit_status = ERR_BI;
		ret = 0;
	}
	if ((*node)->right)
		ret = check_neighbors(&(*node)->right, data);
	return (ret);
}
