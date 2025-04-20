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

static	void	init_vars(int *i, int *j, t_data *data, char *fst, char *last);

/* 
'pat' var name is short for 'pattern'
'name' var name is file name
*/
char	*match_begin(char *pat, char *name, t_data *data)
{
	char	*substr;
	char	*ast_pos;

	data->wild->bgn = true;
	if (*pat != *name)
		return (0);
	ast_pos = next_ast(pat);
	*ast_pos = 0;
	substr = ft_strstr(name, pat);
	*ast_pos = '*';
	return (substr);
}

char	*match_end(char *pat, char *name, t_data *data)
{
	int	pat_len;
	int	name_len;
	char	*substr;

	data->wild->end = true;
	pat_len = ft_strlen(pat);
	name_len = ft_strlen(name);
	substr = ft_strstr(&name[name_len - pat_len], pat);
	return (substr);
}

int	match_mid(char *pat, char *last_ast, char *name, t_data *data)
{
	char	*ast_pos;
	char	*substr;
	int	i;
	int	j;

	init_vars(&i, &j, data, pat ,last_ast);
	pat = find_first_no_ast(pat);
	while (pat && *pat)
	{
		j++;
		ast_pos = next_ast(pat);
		if (ast_pos)
			*ast_pos = 0;
		substr = ft_strstr(name, pat);
		if (substr)
		{
			name = substr + ft_strlen(pat);
			i++;
		}
		if (ast_pos)
			*ast_pos = '*';
		pat = find_first_no_ast(ast_pos);
	}
	*last_ast = '*';
	if (i == j)
		return (1);
	return (0);
}

static	void	init_vars(int *i, int *j, t_data *data, char *fst, char *last)
{
	*i = 0;
	*j = 0;
	while (fst != last)
	{
		if (*fst != '*')
		{
			data->wild->mid = true;
			break;
		}
		fst++;
	}
	*last = 0;
}
