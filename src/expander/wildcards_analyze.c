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

static int	is_matching_pattern(char *pat, char *name, t_data *data);
static int	directory_analyze(char *s, t_data *data);

/* 
'pat' var name is short for 'pattern' 
'name' var name is file name
*/
int	handle_wildcard(t_word *word, t_data *data)
{
	t_word	*last;

	data->wild = ft_calloc(sizeof(t_wildcard), 1);
	if (!data->wild)
		return (error_allocation(data));
	last = word;
	while (word)
	{
		if (ft_strchr(word->word, '*'))
		{
			if (directory_analyze(word->word, data) == -1)
				return (-1);
			update_tword(data, &word, last);
		}
		last = word;
		word = word->next;
	}
        free_wild(data, 0, NULL);
	return (0);
}

static int	directory_analyze(char *s, t_data *data)
{
	DIR	*dir;
	struct dirent	*entry;

	dir = opendir(".");
	if (!dir)
	{
		perror ("Cannot open current directory");
		data->exit_status = 1;
		return (-1);
	}
	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_name[0] != '.' && is_matching_pattern(s, entry->d_name, data))
		{
			if (create_word_node(entry->d_name, data) == -1)
				return (free_wild(data,1, dir));
		}
		reset_bool(data);
		entry = readdir(dir);
	}
	closedir(dir);
	return (0);
}

/*
first_ast and last_ast means asterisk
*/
static int	is_matching_pattern(char *pat, char *name, t_data *data)
{
	char	*last_ast;
	char	*first_ast;

	last_ast = NULL;
	first_ast = next_ast(pat);
	last_ast = get_last_ast(pat);
	if (*pat != '*' && match_begin(pat, name, data))
	{
		name = name + ft_strlen(pat) - ft_strlen(next_ast(pat));
		data->wild->bgn_ok = true;
	}
	if (*(last_ast + 1) && match_end(last_ast + 1, name, data))
		data->wild->end_ok = true;
	if (first_ast != last_ast && match_mid(first_ast, last_ast, name, data))
		data->wild->mid_ok = true;
	return (verify_match(data));
}
