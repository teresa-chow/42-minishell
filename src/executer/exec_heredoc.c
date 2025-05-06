/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_hereeoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42porto.com>    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-05 08:12:23 by carlaugu          #+#    #+#             */
/*   Updated: 2025-05-05 08:12:23 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execute.h"

int    search_heredoc(t_data *data, t_tree_node **node)
{
        t_tree_node     *tmp;
        int             i;

        i = 0;
        tmp = *node;
        if (tmp->left)
        {
                if (search_heredoc(data, &tmp->left) != 0)
                        return (-1);
        }
        i = redir_heredoc(data, tmp->word);
        if (tmp->right)
        {
                if (search_heredoc(data, &tmp->right) != 0)
                        return (-1);
        }
        return (i);
}

void	close_heredoc_fds(t_data *data, t_tree_node *node)
{
	t_word  *tmp;

        if (!node)
		node = data->ast_root;
        tmp = node->word;        
	if (node->left)
		close_heredoc_fds(NULL, node->left);
        while (tmp)
        {
                if (tmp->in_fd)
		        close(tmp->in_fd);
                tmp = tmp->next;
        }
	if (node->right)
		close_heredoc_fds(NULL, node->right);
}
