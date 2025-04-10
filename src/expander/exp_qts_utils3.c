/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_qts_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:23:30 by carlaugu          #+#    #+#             */
/*   Updated: 2025/04/10 17:13:18 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expand.h"

void	update_quotes_exp_status(char *ptr, t_data *data)
{
	if (*ptr == '\'')
		data->exp->in_sing = !data->exp->in_sing;
	else if (*ptr == '"')
		data->exp->in_dbl = !data->exp->in_dbl;
}

int	expand_tilde(t_word **word, t_data *data)
{
	char	*equal_pos;
	char	*to_free;
	char	box;

	if (!data->env_home_var)
	{
		if (handle_with_home(data) == -1)
			return (-1);
	}
	to_free = (*word)->word;
	if (data->exp->til_aft_equal)
	{
		equal_pos = ft_strchr((*word)->word, '=');
		box = *(equal_pos + 1);
		*(equal_pos + 1) = 0;	
		(*word)->word = ft_strjoin((*word)->word, data->env_home_var);
		if (!(*word)->word)
			return (-1);
		*(equal_pos + 1)= box;
	}
	else
		(*word)->word = data->env_home_var;
	free (to_free);
	if (data->no_home)
		free(data->env_home_var);
	return (0);
}

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

void	join_splited_words(t_data *data, char **tmp)
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
