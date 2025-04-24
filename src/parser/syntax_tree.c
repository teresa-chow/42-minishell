/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 18:20:27 by tchow-so          #+#    #+#             */
/*   Updated: 2025/04/24 16:09:58 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/utils.h"

static t_word_lst	*find_pivot(t_word_lst *start, t_word_lst *end);
static void			handle_cmd_group(t_data *data, t_word_lst *pivot,
						t_tree_node **node);
static void			rm_parentheses(t_data *data, t_word_lst *word_lst,
						t_tree_node **node);

void	create_syntax_tree(t_data *data, t_word_lst *start, t_word_lst *end,
	t_tree_node **node)
{
	t_word_lst	*pivot;
	t_word_lst	*new_start;
	t_word_lst	*new_end;

	new_start = NULL;
	new_end = NULL;
	pivot = find_pivot(start, end);
	if (pivot->word->word[0] == '(')
	{
		handle_cmd_group(data, pivot, node);
		return ;
	}
	fill_node(data, pivot, node);
	if ((*node)->type != CMD)
	{
		new_end = last_partition_node(start, pivot);
		(*node)->left = add_node();
		create_syntax_tree(data, start, new_end, &(*node)->left);
		new_start = first_partition_node(pivot);
		(*node)->right = add_node();
		create_syntax_tree(data, new_start, end, &(*node)->right);
	}
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

static void	handle_cmd_group(t_data *data, t_word_lst *pivot, t_tree_node **node)
{
	(*node)->word = ft_calloc(1, sizeof(t_word));
	(*node)->word->word = ft_strdup("()");
	(*node)->type = GROUP;
	(*node)->left = add_node();
	rm_parentheses(data, pivot, &(*node)->left);
}

static void	rm_parentheses(t_data *data, t_word_lst *word_lst,
	t_tree_node **node)
{
	char		*tmp_group;
	char		**cmd_lst;
	t_word_lst	*tmp_lst;

	tmp_group = ft_substr(word_lst->word->word, 1,
			ft_strlen(word_lst->word->word) - 2);
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
		create_syntax_tree(data, tmp_lst, NULL, node);
		free(tmp_lst);
	}
}
