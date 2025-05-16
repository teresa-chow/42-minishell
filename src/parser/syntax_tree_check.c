/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_tree_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:30:33 by tchow-so          #+#    #+#             */
/*   Updated: 2025/05/16 18:19:33 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/errors.h"
#include "../../include/utils.h"

static int	check_neighbors(t_tree_node **node, t_data *data);

//t_word_lst *word_lst
int check_syntax_tree(t_tree_node **root, t_data *data)
{
	if (!check_neighbors(root, data))
	{
		ft_printf("data->exit_status: %d\n", data->exit_status);
		return (0);
	}
	//if node->type == GROUP && node->word->next->word //exit_status updated and error msg already printed
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
		&& ((*node)->left->type != AND && (*node)->left->type != OR))
	{
		data->status = ERR_BI;
		ret = 0;
	}
	if ((*node)->right)
		ret = check_neighbors(&(*node)->right, data);
	return (ret);
}