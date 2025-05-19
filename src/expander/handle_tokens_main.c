/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tokens_main.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:25:40 by carlaugu          #+#    #+#             */
/*   Updated: 2025/05/19 22:58:54 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expand.h"

static int	handle_process(t_data *data, t_word **word, t_word **last,
				t_tree_node **node);
static int	process_token(t_word **word, t_data *data);
static void	delete_node(t_word **curr, t_word **last, t_tree_node **node,
				t_word **prev);
static void	update_word_and_reset_flag(t_data *data, t_word **word);

int	handle_tokens(t_word *word, t_data *data, t_tree_node **node)
{
	t_word	*last;

	data->exp = ft_calloc(sizeof(t_expand), sizeof(char));
	if (!data->exp)
		return (error_allocation(data));
	last = NULL;
	while (word)
	{
		data->exp->prev = word;
		data->word = &word;
		if (analyze_token_context(&word, data) == -1)
			return (free_exp(data, 1));
		if (data->exp->has_dbl || data->exp->has_sing || data->exp->has_exp)
		{
			if (handle_process(data, &word, &last, node) == -1)
				return (free_exp(data, 1));
			reset_big_part_flags(data);
		}
		if (word && data->exp->prev)
			word = word->next;
		last = data->exp->prev;
	}
	free_exp(data, 0);
	return (0);
}

static int	handle_process(t_data *data, t_word **word, t_word **last,
	t_tree_node **node)
{
	if (process_token(word, data) == -1)
		return (-1);
	if (!(*word)->word && node)
	{
		delete_node(word, last, node, &data->exp->prev);
		if (data->to_null && !(*node)->word)
			data->to_null->word = NULL;
		else
			data->to_null->word = (*node)->word;
	}
	return (0);
}

static int	process_token(t_word **word, t_data *data)
{
	char	*cpy;
	char	*start;
	int		i;

	cpy = ft_strdup((*word)->word);
	if (!cpy)
		return (-1);
	start = cpy;
	while (*cpy)
	{
		if (*cpy == '\'' || *cpy == '"')
			i = handle_quotes(&cpy, data);
		else
			i = exp_join_segment(data, &cpy, 0, NULL);
		if (i == -1)
			return (-1);
		update_word_and_reset_flag(data, word);
	}
	data->exp->new = NULL;
	free(start);
	return (0);
}

static	void	update_word_and_reset_flag(t_data *data, t_word **word)
{
	reset_small_part_flags(data);
	if ((*word)->word != data->exp->new)
		free((*word)->word);
	(*word)->word = data->exp->new;
}

static void	delete_node(t_word **curr, t_word **last, t_tree_node **node,
	t_word **prev)
{
	t_word	*next;
	t_word	*tmp;

	tmp = (*node)->word;
	while (tmp)
	{
		if (tmp->next == *curr)
			tmp->next = (*curr)->next;
		tmp = tmp->next;
	}
	next = (*curr)->next;
	*prev = NULL;
	if (*last)
		(*last)->next = (*curr)->next;
	if ((*node)->word == *curr)
		(*node)->word = (*curr)->next;
	free(*curr);
	*curr = next;
}
