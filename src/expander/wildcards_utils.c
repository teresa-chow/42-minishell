/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:35:44 by carlaugu          #+#    #+#             */
/*   Updated: 2025/04/30 17:35:57 by tchow-so         ###   ########.fr       */
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
	bool	in_dbl;
	bool	in_sing;

	in_dbl = false;
	in_sing = false;
	ast = NULL;
	while (*s)
	{
		if (*s == '"' && !in_sing && !in_dbl)
			in_dbl = true;
		else if (*s == '"' && in_dbl)
			in_dbl = false;
		if (*s == '\'' && !in_sing && !in_dbl)
			in_sing = true;
		else if (*s == '\'' && in_sing)
			in_sing = false;
		if (*s == '*' && !in_sing && !in_dbl) 
			ast = s;
		s++;
	}
	return (ast);
}

char	*next_ast(char *s)
{
	bool	in_dbl;
	bool	in_sing;

	in_dbl = false;
	in_sing = false;
	while (*s)
	{
		if (*s == '"' && !in_sing && !in_dbl)
			in_dbl = true;
		else if (*s == '"' && in_dbl)
			in_dbl = false;
		if (*s == '\'' && !in_sing && !in_dbl)
			in_sing = true;
		else if (*s == '\'' && in_sing)
			in_sing = false;
		if (*s == '*' && !in_sing && !in_dbl) 
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
