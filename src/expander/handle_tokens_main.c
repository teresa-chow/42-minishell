/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_qts_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:25:40 by carlaugu          #+#    #+#             */
/*   Updated: 2025/04/10 17:54:09 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expand.h"

static void	delete_node(t_word **curr, t_word **last, t_tree_node **node);
static int	handle_process(t_data *data, t_word **word, t_word **last, t_tree_node **node);
static int	process_token(t_word **word, t_data *data);

int	handle_tokens(t_word *word, t_data *data, t_tree_node **node)
{
	t_word	*last;

	data->exp = ft_calloc(sizeof(t_expand), sizeof(char));
	if (!data->exp)
		return (error_allocation(data));
	last = NULL;
	while (word)
	{
			data->word = &word;
		if (analyze_token_context(&word, data) == -1)
			return(free_exp(data, 1));
		if (data->exp->has_dbl || data->exp->has_sing || data->exp->has_exp)
		{
			if (handle_process(data, &word, &last, node) == -1)
				return (free_exp(data, 1));
			reset_big_part_flags(data);
		}
		last = word;
		if (word)
			word = word->next;
	}
	return (0);
}

static int	handle_process(t_data *data, t_word **word, t_word **last, t_tree_node **node)
{
	if (process_token(word, data) == -1)
		return(-1);
	if (!(*word)->word)
		delete_node(word, last, node);
	return (0);
}

static int	process_token(t_word **word, t_data *data)
{
	char	*ptr;
	char	*start;
	int	i;

	ptr = ft_strdup((*word)->word);
	if (!ptr)
		return (-1);
	start = ptr;
	while (*ptr)
	{
		if (*ptr == '$' && (*(ptr + 1) == '\'' || *(ptr + 1) == '"'))
			ptr++;
		if (*ptr == '\'' || *ptr == '"')
			i = handle_quotes(&ptr, data);
		else
			i = exp_join_segment(data, &ptr, 0, NULL);
		if (i == -1)
			return (-1);
		reset_small_part_flags(data);
		if ((*word)->word != data->exp->new)
			free((*word)->word);
		(*word)->word = data->exp->new;
	}
	data->exp->new = NULL;
	free(start);
	return (0);
}

static void	delete_node(t_word **curr, t_word **last, t_tree_node **node)
{
	if (*last)
		(*last)->next = (*curr)->next;
	if ((*node)->word == *curr)
		(*node)->word = (*curr)->next;
	free(*curr);
	*curr = *last;
}
