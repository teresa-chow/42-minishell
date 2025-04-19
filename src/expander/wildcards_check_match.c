/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_check_match.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42porto.com>    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-19 14:37:09 by carlaugu          #+#    #+#             */
/*   Updated: 2025-04-19 14:37:09 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expand.h"

/* 
'pat' var name is short for 'pattern' 
'name' var name is file name
*/
char	*match_begin(char *pat, char *name)
{
	char	*substr;
	char	*ast_pos;

	if (*pat != *name)
		return (0);
	ast_pos = next_ast(pat);
	*ast_pos = 0;
	substr = ft_strstr(name, pat);
	*ast_pos = '*';
	return (substr);
}

char	*match_end(char *pat, char *name)
{
	int	pat_len;
	int	name_len;
	char	*substr;

	if (!*pat)
		return (NULL);
	pat_len = ft_strlen(pat);
	name_len = ft_strlen(name);
	substr = ft_strstr(&name[name_len - pat_len], pat);
	return (substr);
}

char	*match_mid(char *pat, char *last_ast, char *name)
{
	char	*substr;
	char	*ast_pos;

	(void)last_ast;
	*last_ast = 0;
	pat = find_first_no_ast(pat);
	substr = NULL;
	while (!substr && pat)
	{
		ast_pos = next_ast(pat);
		if (ast_pos)
			*ast_pos = 0;
		substr = ft_strstr(name, pat);
		if (ast_pos)
		{
			pat = ast_pos + 1;
			*ast_pos = '*';
		}
		else
			pat = NULL;
	}
	*last_ast = '*';
	return (substr);
}