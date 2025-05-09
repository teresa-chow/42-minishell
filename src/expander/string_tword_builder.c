/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_tword_builder.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:23:30 by carlaugu          #+#    #+#             */
/*   Updated: 2025/04/30 23:52:04 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expand.h"

static int	create_new_nodes(t_data *data, t_word **last);
static int	update_word(t_data *data, t_word **word);

int	build_new(t_data *data, char *bgn, char *end, int len)
{
	int		total;
	char	*tmp;

	total = ft_strlen(data->exp->new) + len + 1;
	tmp = data->exp->new;
	data->exp->new = ft_calloc(total, sizeof(char));
	if (!data->exp->new)
		return (-1);
	if (tmp)
	{
		ft_strlcpy(data->exp->new, tmp, total);
		add_chars(bgn, end, ft_strchr(data->exp->new, 0));
	}
	else
		add_chars(bgn, end, data->exp->new);
	return (0);
}

int	rebuild_tword(t_data *data, t_word **word, char *to_splt)
{
	t_word	*old_next;
	t_word	*last;

	old_next = (*word)->next;
	data->exp->words = get_words(to_splt);
	if (!data->exp->words)
		return (-1);
	if (update_word(data, word) == -1)
		return (-1);
	last = *word;
	if (create_new_nodes(data, &last) == -1)
		return (-1);
	last->next = old_next;
	*word = last;
	free (data->exp->new);
	data->exp->new = last->word;
	free_strarray(data->exp->words);
	data->exp->words = 0;
	return (0);
}

static int	update_word(t_data *data, t_word **word)
{
	if ((*word)->word != data->exp->new)
		free((*word)->word);
	if (!data->exp->new)
		(*word)->word = ft_strdup(data->exp->words[0]);
	else
		(*word)->word = ft_strjoin(data->exp->new, data->exp->words[0]);
	if (!(*word)->word)
		return (-1);
	return (0);
}

static int	create_new_nodes(t_data *data, t_word **last)
{
	int		i;
	t_word	*tmp;

	i = 0;
	tmp = NULL;
	while (data->exp->words[++i])
	{
		tmp = ft_calloc(sizeof(t_word), sizeof(char));
		if (!tmp)
			return (-1);
		(*last)->next = tmp;
		tmp->word = ft_strdup(data->exp->words[i]);
		if (!tmp->word)
			return (-1);
		if (data->exp && data->exp->in_qt)
			tmp->in_quote = data->exp->in_qt;
		*last = tmp;
	}
	data->exp->in_dbl = 0;
	return (0);
}

int	join_split_words(t_data *data, char **tmp, char *val)
{
	int	i;
	int	j;

	data->exp->words = get_words(val);
	if (!data->exp->words)
		return (-1);
	i = -1;
	while (data->exp->words[++i])
	{
		j = -1;
		while (data->exp->words[i][++j])
			*(*tmp)++ = data->exp->words[i][j];
		if (data->exp->words[i + 1])
			*(*tmp)++ = ' ';
	}
	free_strarray(data->exp->words);
	data->exp->words = 0;
	return (0);
}
