/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:48:41 by tchow-so          #+#    #+#             */
/*   Updated: 2025/04/30 14:19:39 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/errors.h"

static int	quoted_len(char *word);
static	void	add_no_quotes(char **str, char **new);
int	remove_quotes(char **str, bool to_free, t_data *data);

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
	int	len;
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
	int	len;

	len = 0;
	while (*word)
	{
		if (*word != '\'' && *word != '"')
			len++;
		word++;
	}
	return (len);
}

static	void	add_no_quotes(char **str, char **new)
{
	int	i;

	i = -1;
	while (**str)
	{
		if (**str != '\'' && **str != '"')
			new[0][++i] = *(*str);
		(*str)++;
	}
}
