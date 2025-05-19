/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast_pipeline_utils2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-19 20:36:44 by carlaugu          #+#    #+#             */
/*   Updated: 2025-05-19 20:36:44 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execute.h"

void	to_delete(t_data *data, t_word *word, t_tree_node *node)
{
	if (node->left)
		to_delete(data, word, node->left);
	if (node->word == word)
		data->to_null = node;
	if (node->right)
		to_delete(data, word, node->right);
}

void	close_fd(t_data *data)
{
	if (data->fd_copy > 0)
	{
		close(data->fd_copy);
		data->fd_copy = -1;
	}
}
