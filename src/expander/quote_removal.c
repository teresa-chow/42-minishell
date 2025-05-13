/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:48:41 by tchow-so          #+#    #+#             */
/*   Updated: 2025/05/13 16:26:51 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/errors.h"

int			remove_quotes(char **str, bool to_free, t_data *data, t_word *word);
static int	quoted_len(char *word, t_word *word_lst);
static void	add_no_quotes(char **str, char **new, t_word *word);

char	find_in(char *s)
{
	while (*s)
	{
		if (*s == '\'' || *s == '"')
			break ;
		s++;
	}
	return (*s);
}

int	process_remove_quotes(t_word *word, t_data *data)
{
	while (word)
	{
		if (remove_quotes(&word->word, 1, data, word) == -1)
			return (-1);
		word = word->next;
	}
	return (0);
}

int	remove_quotes(char **str, bool to_free, t_data *data, t_word *word)
{
	int		len;
	char	*new;
	char	*start;

	len = 0;
	start = *str;
	if (ft_strchr(*str, '\'') || ft_strchr(*str, '"'))
	{
		len = quoted_len(*str, word);
		new = ft_calloc(len + 1, sizeof(char));
		if (!new)
			return (error_allocation(data));
		*str = start;
		add_no_quotes(str, &new, word);
		if (to_free)
			free(start);
		*str = new;
	}
	return (0);
}

static int	quoted_len(char *word, t_word *word_lst)
{
	int		len;
	char	in_qt;
	bool	in;

	len = 0;
	in = false;
	in_qt = 0;
	(void)word_lst;
	while (*word)
	{
		if (is_quote(*word) && ft_strchr(word + 1, *word) && !in)
		{
			in_qt = *(word)++;
			in = true;
		}
		if (*word != in_qt)
			len++;
		if (*word == in_qt && in)
		{
			in_qt = 0;
			in = false;
		}
		word++;
	}
	return (len);
}

static	void	add_no_quotes(char **str, char **new, t_word *word)
{
	int		i;
	char	in_qt;
	bool	in;

	i = -1;
	in = false;
	in_qt = 0;
	(void)word;
	while (**str)
	{
		if (is_quote(**str) && ft_strchr(*str + 1, **str) && !in)
		{
			in_qt = *(*str)++;
			in = true;
		}
		if (**str != in_qt)
			new[0][++i] = *(*str);
		if (**str == in_qt && in)
		{
			in_qt = 0;
			in = false;
		}
		(*str)++;
	}
}
