/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tilde.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:36:18 by carlaugu          #+#    #+#             */
/*   Updated: 2025/04/17 11:05:06 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expand.h"

static int	expand_tilde_to_export(t_data *data, t_word **word);
static int	update_word(t_data *data, t_word **word);

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
		if (update_word(data, word) == -1)
			return (1);
	}
	free (to_free);
	return (0);
}

static int	update_word(t_data *data, t_word **word)
{
	char	*slash_pos;

	slash_pos = ft_strchr(ft_strchr((*word)->word, '~'), '/');
	if (slash_pos)
		(*word)->word = ft_strjoin(data->env_home_var, slash_pos);
	else
		(*word)->word = ft_strdup(data->env_home_var);
	if (!(*word)->word)
		return (-1);
	return (0);
}

static char	*join_three(char *s1, char *s2, char *s3)
{
	size_t	len;
	char	*dst;

	len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	dst = malloc((len + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, s1, ft_strlen(s1) + 1);
	ft_strlcat(dst, s2, len + 1);
	if (s3)
		ft_strlcat(dst, s3, len + 1);
	return (dst);
}

static int	expand_tilde_to_export(t_data *data, t_word **word)
{
	char	*equal_pos;
	char	*slash_pos;
	char	box;

	equal_pos = ft_strchr((*word)->word, '=');
	slash_pos = ft_strchr(ft_strchr((*word)->word, '~'), '/');
	box = *(equal_pos + 1);
	*(equal_pos + 1) = 0;	
	(*word)->word = join_three((*word)->word, data->env_home_var, slash_pos);
	if (!(*word)->word)
		return (-1);
	*(equal_pos + 1) = box;
	return (0);
}
