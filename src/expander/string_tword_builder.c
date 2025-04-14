/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_qts_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:23:30 by carlaugu          #+#    #+#             */
/*   Updated: 2025/04/10 17:20:32 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expand.h"

int	build_new(t_data *data, char *bgn, char *end, int len)
{
	int	total;
	char	*to_free;

	total = ft_strlen(data->exp->new) + len + 1;
	to_free = data->exp->new;
	data->exp->new = ft_calloc(total, sizeof(char));
	if (!data->exp->new)
		return (-1);
	if (to_free)
	{
		ft_strlcpy(data->exp->new, to_free, total);
		add_chars(bgn, end, ft_strchr(data->exp->new, 0));
	}
	else
		add_chars(bgn, end, data->exp->new);
	free(to_free);
	return (0);
}

int	rebuild_tword(t_data *data, t_word **word)
{
	t_word	*old_next;
	t_word	*tmp;
	t_word	*last;
	int	i;

	old_next = (*word)->next;
	data->exp->words = get_words((*word)->word);
	if (!data->exp->words)
		return (-1);
	free((*word)->word);
	(*word)->word = data->exp->words[0];
	i = 0;
	last = *word;
	while (data->exp->words[++i])
	{
		tmp = ft_calloc(sizeof(t_word), sizeof(char));
		if (!tmp)
			return (-1);
		last->next = tmp;
		tmp->word = data->exp->words[i];
		last = tmp;
	}
	last->next = old_next;
	*word = last;
	return (0);
}

void	join_split_words(t_data *data, char **tmp)
{
	int	i;
	int	j;

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
}
