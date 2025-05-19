/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_div_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:13:19 by tchow-so          #+#    #+#             */
/*   Updated: 2025/05/19 23:26:14 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

static void	next_single_quote(const char *str, unsigned int *end);
static void	next_double_quote(const char *str, unsigned int *end);
static int	quote_join_word(char *cmd, int *j, t_word **word, char *quote);

int	handle_quote(char *cmd, int *j, t_word_lst **word_lst, t_word **word)
{
	char	*quote;

	quote = NULL;
	if (is_quote(cmd[*j]))
	{
		quote = ft_substr(cmd, *j, next_quote(cmd, *j, is_quote(cmd[*j])));
		if (!quote)
			return (-1);
		if (*j == 0 || is_redirection(cmd[*j - 1])
			|| is_delimiter(cmd[*j - 1]))
		{
			init_word(*word_lst, word);
			(*word)->word = ft_strdup(quote);
			*j += next_quote(cmd, *j, is_quote(cmd[*j]));
		}
		else
			quote_join_word(cmd, j, word, quote);
		free(quote);
	}
	return (0);
}

unsigned int	next_quote(const char *str, unsigned int start, int code)
{
	unsigned int	end;

	end = start + 1;
	if (code == 1)
		next_single_quote(str, &end);
	else if (code == 2)
		next_double_quote(str, &end);
	return (end - start);
}

static void	next_single_quote(const char *str, unsigned int *end)
{
	while (str[*end] && (str[*end] != '\''))
		++*end;
	if (str[*end] && (str[*end] == '\''))
		++*end;
	while (str[*end] && (!is_operator(str[*end])
			|| (str[*end] == '&' && !is_equal_next(str, *end)))
		&& !is_delimiter(str[*end]) && !is_redirection(str[*end])
		&& str[*end] != '\'' && str[*end] != '(' && str[*end] != ')')
	{
		if (str[*end] == '\"')
			break ;
		++*end;
	}
}

static void	next_double_quote(const char *str, unsigned int *end)
{
	while (str[*end] && (str[*end] != '\"'))
		++*end;
	if (str[*end] && (str[*end] == '\"'))
		++*end;
	while (str[*end] && (!is_operator(str[*end])
			|| (str[*end] == '&' && !is_equal_next(str, *end)))
		&& !is_delimiter(str[*end]) && !is_redirection(str[*end])
		&& str[*end] != '\"' && str[*end] != '(' && str[*end] != ')')
	{
		if (str[*end] == '\'')
			break ;
		++*end;
	}
}

static int	quote_join_word(char *cmd, int *j, t_word **word, char *quote)
{
	char	*tmp;

	tmp = ft_strdup((*word)->word);
	free((*word)->word);
	(*word)->word = ft_strjoin(tmp, quote);
	free(tmp);
	if (!(*word)->word)
		return (-1);
	*j += next_quote(cmd, *j, is_quote(cmd[*j]));
	return (0);
}
