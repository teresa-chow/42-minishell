/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_tree_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:56:56 by tchow-so          #+#    #+#             */
/*   Updated: 2025/03/21 14:37:58 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/utils.h"

t_tree_node	*add_node(int index, t_word *word)
{
	t_tree_node	*new;
	
	new = ft_calloc(1, sizeof(t_tree_node));
	if (!new)
		return (NULL);
	new->index = index;
	new->word = word;
	return(new);
}

t_word_lst	*last_op(t_word_lst *word_lst)
{
	t_word_lst	*tmp_lst;
	t_word_lst	*last_op;

	tmp_lst = word_lst;
	last_op = NULL;
	while (tmp_lst->next)
		tmp_lst = tmp_lst->next;
	if (is_operator(tmp_lst->word->word[0]))
		last_op = tmp_lst;
	return (last_op);
}
