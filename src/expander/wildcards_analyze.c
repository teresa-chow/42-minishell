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
static int	directory_analyze(char *s, t_word *word, t_data *data);

/* 
'pat' var name is short for 'pattern' 
'name' var name is file name
*/
///  free_data->wild here and when fail something of memory 
int	handle_wildcard(t_word *word, t_data *data)
{
	t_word	*last;
	t_word	*last_new;

	data->wild = ft_calloc(sizeof(t_wildcard), 1);
	if (!data->wild)
		return (1);
	last = word;
	while (word)
	{
		if (ft_strchr(word->word, '*'))
		{
			directory_analyze(word->word, word, data);
			if (data->wild->wild_word)
			{
				last_new = last_word(data->wild->wild_word);
				last_new->next = word->next;
				free(word->word);
				free(word);
				last->next = data->wild->wild_word;
				word = last_new;
				data->wild->wild_word = NULL;
			}
		}
		last = word;
		word = word->next;
	}
        free_wild(data);
	return (0);
}


// openDIR and CLOSEDIR <<<<-------------------
static int	directory_analyze(char *s, t_word *word, t_data *data)
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
		if (entry->d_name[0] != '.' && is_matching_pattern(s, entry->d_name, data))
			create_word_node(entry->d_name, data);
		reset_bool(data);
		entry = readdir(dir);
	}
	closedir(dir); // if fail???
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
		data->wild->bgn_ok = true;
	if (*(last_ast + 1) && match_end(last_ast + 1, name, data))
		data->wild->end_ok = true;
	if (first_ast != last_ast && match_mid(first_ast, last_ast, name, data))
		data->wild->mid_ok = true;
	return (verify_match(data));
}
