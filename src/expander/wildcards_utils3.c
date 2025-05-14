/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 19:26:48 by carlaugu          #+#    #+#             */
/*   Updated: 2025/05/13 22:09:08 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expand.h"
#include "../../include/errors.h"

int	has_quotes(char *s)
{
	while (*s)
	{
		if (*s == '\'' || *s == '"')
			return (1);
		s++;
	}
	return (0);
}

void	find_substr(char **name, char *tmp, int *i)
{
	char	*substr;

	substr = ft_strstr(*name, tmp);
	if (substr)
	{
		*name = substr + ft_strlen(tmp);
		(*i)++;
	}
}

int	handle_ast_quotes(char **ast_p, char *pat, char **tmp, t_data *data)
{
	*ast_p = next_ast(pat);
	if (*ast_p)
		**ast_p = 0;
	if (has_quotes(pat))
	{
		data->wild->has_quotes = true;
		if (remove_quotes(tmp, false, data) == -1)
			return (-1);
	}
	return (0);
}

void	reset_data(t_data *data, bool *build_new)
{
	reset_bool(data);
	*build_new = false;
}
