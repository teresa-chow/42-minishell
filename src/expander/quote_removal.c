/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:48:41 by tchow-so          #+#    #+#             */
/*   Updated: 2025/04/22 21:36:40 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

int	remove_quotes(t_word *word)
{
	int	len;
	char	*tmp;
	char	*new;
	int	i;

	len = 0;
	tmp = NULL;
	while (word)
	{
		if (ft_strchr(word->word, '\'') || ft_strchr(word->word, '"'))
		{
			tmp = word->word;
			while (*tmp)
			{
				if (*tmp != '\'' && *tmp != '"')
					len++;
				tmp++;
			}
			new = ft_calloc(len + 1, sizeof(char));
			// if (!new)
			tmp = word->word;
			i = -1;
			while (*tmp)
			{
				if (*tmp != '\'' && *tmp != '"')
					new[++i] = (*tmp)++;
				tmp++;
			}
			free(word->word);
			word->word = new;
		}
		word = word->next;
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