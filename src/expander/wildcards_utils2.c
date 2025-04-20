/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42porto.com>    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-19 22:35:17 by carlaugu          #+#    #+#             */
/*   Updated: 2025-04-19 22:35:17 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expand.h"

int	create_word_node(char *name, t_data *data)
{
	t_word	*new;
	t_word	*last;

	new = ft_calloc(sizeof(t_word), 1);
	if (!new)
		return (-1);
	if (!data->wild->wild_word)
		data->wild->wild_word = new;
	else
	{
		last = last_word(data->wild->wild_word);
		last->next = new;
	}
	new->word = ft_strdup(name);
	if (!new->word)
		return (-1);
	return (0);
}

int	verify_match(t_data *data)
{
	t_wildcard	*wild;

	wild = data->wild;
	if (wild->bgn && wild->mid && wild->end)
		return (wild->bgn_ok && wild->mid_ok && wild->end_ok);
	if (wild->bgn && !wild->mid && !wild->end)
		return (wild->bgn_ok);
	if (!wild->bgn && wild->mid && !wild->end)
		return (wild->mid_ok);
	if (!wild->bgn && !wild->mid && wild->end)
		return (wild->end_ok);
	if (wild->bgn && wild->mid && !wild->end)
		return (wild->bgn_ok && wild->mid_ok);
	if (!wild->bgn && wild->mid && wild->end)
		return (wild->mid_ok && wild->end_ok);
	if (wild->bgn && !wild->mid && wild->end)
		return (wild->bgn_ok && wild->end_ok);
	return (0);
}


void	reset_bool(t_data *data)
{
	data->wild->bgn_ok =false;
	data->wild->mid_ok =false;
	data->wild->end_ok =false;
}
