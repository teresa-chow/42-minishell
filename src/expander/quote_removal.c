/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:48:41 by tchow-so          #+#    #+#             */
/*   Updated: 2025/04/30 23:46:39 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/errors.h"

int			remove_quotes(char **str, bool to_free, t_data *data);
static int	quoted_len(char *word);
static void	add_no_quotes(char **str, char **new);

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
	char	*tmp;
	char	first_quote;

	len = 0;
	tmp = word;
	first_quote = 0;
	while (*tmp) ///// add
	{
		if (*tmp == '\'' || *tmp == '"')
		{
			first_quote = *tmp;
			break ;
		}
		tmp++;
	}
	while (*word)
	{
		if (*word != first_quote)
			len++;
		word++;
	}
	return (len);
}

static	void	add_no_quotes(char **str, char **new)
{
	int		i;
	char	*tmp;
	char	first_quote;

	i = -1;
	tmp = *str;
	first_quote = 0;
	while (*tmp) ////// add
	{
		if (*tmp == '\'' || *tmp == '"')
		{
			first_quote = *tmp;
			break ;
		}
		tmp++;
	}
	while (**str)
	{
		if (**str != first_quote)
			new[0][++i] = *(*str);
		(*str)++;
	}
}
