/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:35:44 by carlaugu          #+#    #+#             */
/*   Updated: 2025/04/22 14:20:25 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expand.h"

int	free_wild(t_data *data, int i, DIR *dir)
{
	if (i)
	{
		free_words(&data->wild->wild_word);
		closedir(dir);
	}
	ft_bzero(data->wild, sizeof(t_wildcard));
	free(data->wild);
	data->wild = NULL;
	if (i)
		return (error_allocation(data));
	return (0);
}

char	*get_last_ast(char *s)
{
	char	*ast;
	while (*s)
	{
		if (*s == '*')
			ast = s;
		s++;
	}
	return (ast);
}

char	*next_ast(char *s)
{
	while (*s)
	{
		if (*s == '*')
			return (s);
		s++;
	}
	return (NULL);
}

char	*find_first_no_ast(char *s)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s != '*')
			return (s);
		s++;
	}
	return (s);
}

t_word	*last_word(t_word *tmp_word)
{
	while (tmp_word)
	{
		if (!tmp_word->next)
			break;
		tmp_word = tmp_word->next;
	}
	return (tmp_word);
}
