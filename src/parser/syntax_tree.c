/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 18:20:27 by tchow-so          #+#    #+#             */
/*   Updated: 2025/05/16 12:35:40 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/errors.h"
#include "../../include/utils.h"

static t_word_lst	*find_pivot(t_word_lst *start, t_word_lst *end);
static int			handle_cmd_group(t_word_lst *pivot, t_tree_node **node);
static void			rm_parentheses(t_word_lst *word_lst, t_tree_node **node);

void	create_syntax_tree(t_word_lst *start, t_word_lst *end,
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
		handle_cmd_group(pivot, node);
		free(pivot->word->word);
		free(pivot->word);
		return ;
	}
	fill_node(pivot, node);
	if ((*node)->type != CMD)
	{
		new_end = last_partition_node(start, pivot);
		(*node)->left = add_node();
		create_syntax_tree(start, new_end, &(*node)->left);
		new_start = first_partition_node(pivot);
		(*node)->right = add_node();
		create_syntax_tree(new_start, end, &(*node)->right);
	}
	return ;
}

static t_word_lst	*find_pivot(t_word_lst *start, t_word_lst *end)
{
	t_word_lst	*tmp_lst;
	t_word_lst	*pivot;
	int			precedence;

	tmp_lst = start;
	pivot = start;
	precedence = 2;
	while (start && tmp_lst != end)
	{
		if (precedence > 0
			&& ((!ft_strcmp(tmp_lst->word->word, "&&"))
				|| (!ft_strcmp(tmp_lst->word->word, "||"))))
		{
			pivot = tmp_lst;
			precedence = 0;
		}
		else if (precedence > 1
			&& !ft_strcmp(tmp_lst->word->word, "|"))
		{
			pivot = tmp_lst;
			precedence = 1;
		}
		tmp_lst = tmp_lst->next;
	}
	return (pivot);
}

static int	handle_cmd_group(t_word_lst *pivot, t_tree_node **node)
{
	if (pivot->word->next)
	{
		if (pivot->word->next->word[0] == '(')
			err_syntax("(");
		else
			err_syntax(pivot->word->next->word);
	}
	(*node)->word = ft_calloc(1, sizeof(t_word));
	(*node)->word->word = ft_strdup("()");
	(*node)->type = GROUP;
	(*node)->left = add_node();
	rm_parentheses(pivot, &(*node)->left);
	return (0);
}

static void	rm_parentheses(t_word_lst *word_lst, t_tree_node **node)
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
		create_syntax_tree(tmp_lst, NULL, node);
		free_word_lst(&tmp_lst);
	}
}
