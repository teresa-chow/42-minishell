/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_check_match.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:37:09 by carlaugu          #+#    #+#             */
/*   Updated: 2025/04/23 13:57:38 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expand.h"

static	int	find_return(int i, int j);
static	void	init_vars(int *i, int *j, t_data *data, char *fst, char *last);

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

/* 
'pat' var name is short for 'pattern'
'name' var name is file name
*/
char	*match_begin(char *pat, char *name, t_data *data)
{
	char	*substr;
	char	*ast_pos;
	char	*tmp;

	data->wild->bgn = true;
	if ((*pat != '"' && *pat != '\'') && *pat != *name)
		return (0);
	ast_pos = next_ast(pat);
	*ast_pos = 0;
	tmp = pat;	
	if (has_quotes(pat))
		remove_quotes(&tmp, false);
	substr = ft_strstr(name, tmp);
	if (tmp != pat)
		free (tmp);
	*ast_pos = '*';
	return (substr);
}

char	*match_end(char *pat, char *name, t_data *data)
{
	int	pat_len;
	int	name_len;
	char	*substr;

	if (!*pat || !*(pat + 1))
		return (NULL);
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
	return (find_return(i, j));
}

static int	find_return(int i, int j)
{
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
