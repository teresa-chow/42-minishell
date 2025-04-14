/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tilde.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-11 16:36:18 by carlaugu          #+#    #+#             */
/*   Updated: 2025-04-11 16:36:18 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expand.h"

static int	expand_tilde_to_export(t_data *data, t_word **word);

int	expand_tilde(t_word **word, t_data *data)
{
	char	*to_free;

	if (data->no_home)
	{
		if (handle_with_home(data) == -1)
			return (-1);
	}
	to_free = (*word)->word;
	if (data->exp->til_aft_equal)
	{
		if (expand_tilde_to_export(data, word) == -1)
			return (-1);
	}
	else
	{
		(*word)->word = ft_strdup(data->env_home_var);
		if (!(*word)->word)
			return (-1);
	}
	free (to_free);
	return (0);
}

static int	expand_tilde_to_export(t_data *data, t_word **word)
{
	char	*equal_pos;
	char	box;

	equal_pos = ft_strchr((*word)->word, '=');
	box = *(equal_pos + 1);
	*(equal_pos + 1) = 0;	
	(*word)->word = ft_strjoin((*word)->word, data->env_home_var);
	if (!(*word)->word)
		return (-1);
	*(equal_pos + 1) = box;
	return (0);
}
