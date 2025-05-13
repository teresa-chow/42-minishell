/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_check_match.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:37:09 by carlaugu          #+#    #+#             */
/*   Updated: 2025/05/13 22:09:03 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expand.h"

static int	find_return(int i, int j);
static void	init_vars(t_data *data, char *fst, char *last);

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
	int		tmp_len;
	int		name_len;
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
	int		incre[2];

	ft_bzero(incre, sizeof(int) * 2);
	init_vars(data, pat, last_ast);
	pat = find_first_no_ast(pat);
	while (pat && *pat)
	{
		tmp = pat;
		incre[1]++;
		if (handle_ast_quotes(&ast_pos, pat, &tmp, data) == -1)
			return (-1);
		find_substr(&name, tmp, &incre[0]);
		if (ast_pos)
			*ast_pos = '*';
		pat = find_first_no_ast(ast_pos);
	}
	if (data->wild->has_quotes)
		free(tmp);
	*last_ast = '*';
	data->wild->has_quotes = false;
	return (find_return(incre[0], incre[1]));
}

static int	find_return(int i, int j)
{
	if (i == j)
		return (1);
	return (0);
}

static	void	init_vars(t_data *data, char *fst, char *last)
{
	while (fst != last)
	{
		if (*fst != '*')
		{
			data->wild->mid = true;
			break ;
		}
		fst++;
	}
	*last = 0;
}
