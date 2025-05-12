/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 08:12:23 by carlaugu          #+#    #+#             */
/*   Updated: 2025/05/09 11:09:19 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execute.h"

int	search_heredoc(t_data *data, t_tree_node **node)
{
	t_tree_node	*tmp;
	int			i;

	i = 0;
	tmp = *node;
	if (tmp->left)
	{
		if (search_heredoc(data, &tmp->left) != 0)
			return (-1);
	}
	i = redir_heredoc(data, tmp);
	if (tmp->right)
	{
		if (search_heredoc(data, &tmp->right) != 0)
			return (-1);
	}
	return (i);
}

void	close_heredoc_fds(t_data *data, t_tree_node *node)
{
	if (!node)
		node = data->ast_root;
	if (node->left)
		close_heredoc_fds(NULL, node->left);
	if (node->type == CMD && node->fd_in != -1)
	{
		close(node->fd_in);
		node->fd_in = -1;
	}
	if (node->right)
		close_heredoc_fds(NULL, node->right);
}
