/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_tree_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:56:56 by tchow-so          #+#    #+#             */
/*   Updated: 2025/04/04 13:29:34 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/utils.h"

t_word_lst	*last_partition_node(t_word_lst *start, t_word_lst *end)
{
	t_word_lst	*last;

	last = start;
	while (last != end)
		last = last->next;
	return (last);
}

t_word_lst	*first_partition_node(t_word_lst *end)
{
	t_word_lst	*first;

	first = end;
	if (end->next)
		first = end->next;
	return (first);
}

t_tree_node	*add_node(void)
{
	t_tree_node	*new;

	new = ft_calloc(1, sizeof(t_tree_node));
	if (!new)
		return (NULL);
	return (new);
}

void	fill_node(t_word_lst *pivot, int index, t_tree_node **node)
{
	if (!pivot || !*node)
		return ;
	(*node)->word = pivot->word;
	(*node)->index = index;
	if (!ft_strcmp(pivot->word->word, "|"))
		(*node)->type = PIPE;
	else if (!ft_strcmp(pivot->word->word, "&&"))
		(*node)->type = AND;
	else if (!ft_strcmp(pivot->word->word, "||"))
		(*node)->type = OR;
	else if (pivot->word->word[0] == '(')
		(*node)->type = GROUP;
	else
		(*node)->type = CMD;
}
