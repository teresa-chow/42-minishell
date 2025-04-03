/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 18:20:27 by tchow-so          #+#    #+#             */
/*   Updated: 2025/04/03 16:10:47 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/utils.h"

static int	is_group(t_word_lst *word_lst);
static void	rm_parentheses(t_word_lst *word_lst, t_tree_node **root);
static void	find_low_precedence(t_word_lst *word_lst, t_tree_node **root);

void	create_syntax_tree(t_word_lst *word_lst, t_tree_node **root)
{
	if (is_group(word_lst))
		rm_parentheses(word_lst, root);
	else
		find_low_precedence(word_lst, root);
	if ((*root)->type != CMD) //start building subtree: mem alloc left and right nodes
	{
		//(*root)->left = add_node();
		//(*root)->right = add_node();
		ft_printf("root: %s, type: %d\n",
			(*root)->word->word, (*root)->type); //delete
	}
	return ;
}

t_tree_node	*add_node(void)
{
	t_tree_node	*new;

	new = ft_calloc(1, sizeof(t_tree_node));
	if (!new)
		return (NULL);
	return (new);
}

static int	is_group(t_word_lst *word_lst)
{
	if (!word_lst->next && word_lst->word->word[0] == '(')
		return (1);
	return (0);
}

static void	rm_parentheses(t_word_lst *word_lst, t_tree_node **root)
{
	char		*tmp_group;
	char		**cmd_lst;
	t_word_lst	*tmp_lst;

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
		find_low_precedence(tmp_lst, root);
	}
}

static void	find_low_precedence(t_word_lst *word_lst, t_tree_node **root)
{
	t_word_lst	*tmp_lst;

	tmp_lst = word_lst;
	(*root)->word = tmp_lst->word;
	(*root)->type = CMD;
	while (tmp_lst)
	{
		if (!ft_strcmp(tmp_lst->word->word, "|"))
		{
			(*root)->word = tmp_lst->word;
			(*root)->type = PIPE;
		}
		else if (!ft_strcmp(tmp_lst->word->word, "&&"))
		{
			(*root)->word = tmp_lst->word;
			(*root)->type = AND;
		}
		else if (!ft_strcmp(tmp_lst->word->word, "||"))
		{
			(*root)->word = tmp_lst->word;
			(*root)->type = OR;
		}
		tmp_lst = tmp_lst->next;
	}
}
