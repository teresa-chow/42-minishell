/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_check_match.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:37:09 by carlaugu          #+#    #+#             */
/*   Updated: 2025/04/30 13:34:38 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expand.h"

static	int	find_return(int i, int j);
static	void	init_vars(int *i, int *j, t_data *data, char *fst, char *last);

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
		remove_quotes(&tmp, false, data);
	substr = ft_strstr(name, tmp);
	if (tmp != pat)
		free (tmp);
	*ast_pos = '*';
	return (substr);
}

char	*match_end(char *pat, char *name, t_data *data)
{
	int	tmp_len;
	int	name_len;
	char	*substr;
	char	*tmp;

	if (!*pat)
		return (NULL);
	data->wild->end = true;
	tmp = pat;
	if (has_quotes(pat))
		remove_quotes(&tmp, false, data);
	tmp_len = ft_strlen(tmp);
	name_len = ft_strlen(name);
	substr = ft_strstr(&name[name_len - tmp_len], tmp);
	if (tmp != pat)
		free (tmp);
	return (substr);
}

int	match_mid(char *pat, char *last_ast, char *name, t_data *data)
{
	char	*ast_pos;
	char	*tmp;
	bool	has_quotes;
	int	i;
	int	j;

	has_quotes = false;
	init_vars(&i, &j, data, pat ,last_ast);
	pat = find_first_no_ast(pat);
	while (pat && *pat)
	{
		tmp = pat;
		j++;
		if (handle_ast_quotes(&ast_pos, pat, &tmp, &has_quotes) == -1)
			return (-1);
		find_substr(&name, tmp, &i);
		if (ast_pos)
			*ast_pos = '*';
		pat = find_first_no_ast(ast_pos);
	}
	if (has_quotes)
		free(tmp);
	*last_ast = '*';
	has_quotes = false;
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
