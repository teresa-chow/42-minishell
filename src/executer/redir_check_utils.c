/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_check_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:00:34 by tchow-so          #+#    #+#             */
/*   Updated: 2025/05/09 11:10:24 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/execute.h"
#include "../../include/errors.h"
#include "../../include/utils.h"

int	heredoc_redir_in(t_tree_node *node)
{
	t_word	*tmp;
	int		heredoc;

	heredoc = 0;
	tmp = node->word;
	while (tmp)
	{
		if (tmp->redir == IN)
			heredoc = 0;
		if (tmp->redir == HEREDOC)
			heredoc = 1;
		tmp = tmp->next;
	}
	return (heredoc);
}
