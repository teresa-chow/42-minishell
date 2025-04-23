/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:48:41 by tchow-so          #+#    #+#             */
/*   Updated: 2025/04/23 17:38:20 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

int	remove_quotes(char **str, bool to_free);

int	process_remove(t_word *word)
{
	while (word)
	{
		if (remove_quotes(&word->word, 1) == -1)
			return (-1);
		word = word->next;
	}
	return (0);
}

int	remove_quotes(char **str, bool to_free)
{
	int	len;
	char	*new;
	char	*start;
	int	i;

	len = 0;
	i = -1;
	start = *str;
	if (ft_strchr(*str, '\'') || ft_strchr(*str, '"'))
	{
		while (**str)
		{
			if (**str != '\'' && **str != '"')
				len++;
			(*str)++;
		}
		new = ft_calloc(len + 1, sizeof(char));
		// if (!new)
		i = -1;
		*str = start;
		while (**str)
		{
			if (**str != '\'' && **str != '"')
				new[++i] = *(*str);
			(*str)++;
		}
		if (to_free)
			free(start);
		*str = new;
	}
	return (0);
}

/*static int	quoted_len(char *word);
static void	get_word_no_quotes(char *new_word, char *word);

void	quote_removal(t_word *word)
{
	t_word	*tmp;
	char	*new_word;

	tmp = word;
	new_word = NULL;
	while (tmp)
	{
		new_word = ft_calloc(quoted_len(tmp->word) + 1, sizeof(char));
		get_word_no_quotes(new_word, tmp->word);
		free(tmp->word);
		tmp->word = new_word;
		tmp = tmp->next;
	}
}

static int	quoted_len(char *word)
{
	int	len;
	int i;

	len = 0;
	i = 0;
	while (word[i])
	{
		if (is_quote(word[i]))
		{
			len += next_quote(word, i, is_quote(word[i])) - i + 1;
			i += next_quote(word, i, is_quote(word[i]));
		}
		len++;
		i++;
	}
	return (len);
}

static void	get_word_no_quotes(char *new_word, char *word)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (word[i])
	{
		if (word[i] == '\'')
		{
			i++;
			while (word[i] == '\'')
				new_word[j++] = word[i++];
		}
		else if (word[i] == '\"')
		{
			i++;
			while (word[i] == '\"')
				new_word[j++] = word[i++];
		}
		else
			new_word[j++] = word[i++];
	}
}*/