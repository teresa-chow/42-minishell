/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_analyze.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42porto.com>    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-18 17:34:28 by carlaugu          #+#    #+#             */
/*   Updated: 2025-04-18 17:34:28 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expand.h"

static int	is_matching_pattern(char *pat, char *name);
static int	directory_analyze(char *s, t_word **word, t_data *data);

/* 
'pat' var name is short for 'pattern' 
'name' var name is file name
*/
///  free_data->wild here and when fail something of memory 
int	handle_wildcard(t_word **word, t_data *data)
{
	char	*ch;

	ch = ft_strchr((*word)->word, '*');
	if (!ch)
		return (0);
	directory_analyze((*word)->word, word, data);
        // expand_wildcard();
	return (0);
}

// openDIR and CLOSEDIR <<<<-------------------
static int	directory_analyze(char *s, t_word **word, t_data *data)
{
	DIR	*dir;
	struct dirent	*entry;

	(void)s;
	(void)word;
	dir = opendir(".");
	if (!dir)
	{
		perror ("Cannot open current directory");
		data->exit_status = 1;
		// return (444234242);
	}
	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_name[0] != '.' && is_matching_pattern(s, entry->d_name))
			        // expand_wildcard() and create t_word;
		entry = readdir(dir);
	}
	return (0);
}

static int	is_matching_pattern(char *pat, char *name)
{
	char	*last_ast;
	char	*first_ast;

	last_ast = NULL;
	first_ast = next_ast(pat);
	last_ast = get_last_ast(pat);
	if (*pat != '*' && match_begin(pat, name))
		return (1);
	else if (match_end(last_ast + 1, name))
		return (1);
	else if (first_ast != last_ast && match_mid(first_ast, last_ast, name))
		return (1);
	else
		return (0);
}
