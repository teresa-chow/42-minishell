/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:48:41 by tchow-so          #+#    #+#             */
/*   Updated: 2025/05/09 11:15:33 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/errors.h"

int			remove_quotes(char **str, bool to_free, t_data *data);
static int	quoted_len(char *word);
static void	add_no_quotes(char **str, char **new);

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
		if (remove_quotes(&word->word, 1, data) == -1)
			return (-1);
		word = word->next;
	}
	return (0);
}

int	remove_quotes(char **str, bool to_free, t_data *data)
{
	int		len;
	char	*new;
	char	*start;

	len = 0;
	start = *str;
	if (ft_strchr(*str, '\'') || ft_strchr(*str, '"'))
	{
		len = quoted_len(*str);
		new = ft_calloc(len + 1, sizeof(char));
		if (!new)
			return (error_allocation(data));
		*str = start;
		add_no_quotes(str, &new);
		if (to_free)
			free(start);
		*str = new;
	}
	return (0);
}

static int	quoted_len(char *word)
{
	int		len;
	char	in_qt;
	bool	in;

	len = 0;
	in = false;
	in_qt = 0;
	in_qt = find_in(word);
	while (*word)
	{
		if (*word != in_qt)
			len++;
		if (*word == in_qt && in)
		{
			in = false;
			in_qt = find_in(word + 1);
		}
		if (*word == in_qt && !in)
			in = true;
		word++;
	}
	return (len);
}

static	void	add_no_quotes(char **str, char **new)
{
	int		i;
	char	in_qt;
	bool	in;

	i = -1;
	in = false;
	in_qt = find_in(*str);
	while (**str)
	{
		if (**str != in_qt)
			new[0][++i] = *(*str);
		if (**str == in_qt && in)
		{
			in = false;
			in_qt = find_in(*(str) + 1);
		}
		if (**str == in_qt && !in)
			in = true;
		(*str)++;
	}
}
