/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 18:20:27 by tchow-so          #+#    #+#             */
/*   Updated: 2025/04/04 15:49:12 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/utils.h"

static t_word_lst	*find_pivot(t_word_lst *start, t_word_lst *end);
static int	is_group(t_word_lst *word_lst);
static void	handle_cmd_group(t_word_lst *pivot, int index, t_tree_node **node);
static void	rm_parentheses(t_word_lst *word_lst, t_tree_node **node);

void	create_syntax_tree(t_word_lst *start, t_word_lst *end, int index,
	t_tree_node **node)
{
	t_word_lst	*pivot;
	t_word_lst	*new_start;
	t_word_lst	*new_end;

	new_start = NULL;
	new_end = NULL;
	pivot = find_pivot(start, end);
	if (is_group(pivot)) //tmp solution, needs refactoring
	{
		handle_cmd_group(pivot, index, node);
		return ;
	}
	(*node)->word = pivot->word;
	fill_node(pivot, index, node);
	if (index)
		++index;
	if ((*node)->type != CMD)
	{
		new_end = last_partition_node(start, pivot);
		(*node)->left = add_node();
		create_syntax_tree(start, new_end, ++index, &(*node)->left);
		new_start = first_partition_node(pivot);
		(*node)->right = add_node();
		create_syntax_tree(new_start, end, ++index, &(*node)->right);
	}
	ft_printf("(*node)->index: %d | (*node)->word: %s | (*node)->type: %d\n", (*node)->index, (*node)->word->word, (*node)->type);
	return ;
}

static t_word_lst	*find_pivot(t_word_lst *start, t_word_lst *end)
{
	t_word_lst	*tmp_lst;
	t_word_lst	*pivot;

	tmp_lst = start;
	pivot = start;
	while (tmp_lst != end)
	{
		if ((!ft_strcmp(tmp_lst->word->word, "|"))
			|| (!ft_strcmp(tmp_lst->word->word, "&&"))
			|| (!ft_strcmp(tmp_lst->word->word, "||")))
			pivot = tmp_lst;
		tmp_lst = tmp_lst->next;
	}
	return (pivot);
}

static int	is_group(t_word_lst *word_lst)
{
	if (!word_lst->next && word_lst->word->word[0] == '(')
		return (1);
	return (0);
}

// TODO: handle groups, currently only handling single command group as input
static void	handle_cmd_group(t_word_lst *pivot, int index, t_tree_node **node)
{
	if (!index && !pivot->next)
	{
		rm_parentheses(pivot, node);
		return ;
	}
}

static void	rm_parentheses(t_word_lst *word_lst, t_tree_node **node)
{
	char		*tmp_group;
	char		**cmd_lst;
	t_word_lst	*tmp_lst;

	(void)node;
	tmp_group = ft_substr(word_lst->word->word, 1,
		group_len(word_lst->word->word, 0) - 2);
	cmd_lst = tokenize_op(tmp_group);
	if (cmd_lst)
	{
		free(tmp_group);
		tmp_lst = ft_calloc(1, sizeof(t_word_lst));
		if (!tmp_lst)
		{
			free_strarray(cmd_lst);
			return ;
		}
		tokenize_w_lst(cmd_lst, tmp_lst);
		free_strarray(cmd_lst);
		create_syntax_tree(tmp_lst, NULL, 0, node);
		free(tmp_lst);
	}
}