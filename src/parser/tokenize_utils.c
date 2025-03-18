/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:35:45 by tchow-so          #+#    #+#             */
/*   Updated: 2025/03/18 16:25:15 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

int	is_operator(int c)
{
	return (c == '|' || c == '&');
}

int	is_delimiter(int c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

int	is_quote(int c)
{
	if (c == '\'')
		return (1);
	if (c == '\"')
		return (2);
	return (0);
}

int	is_redirection(int c)
{
	return (c == '>' || c == '<');
}

int	is_equal_next(const char *str, int i)
{
	if (!str[i + 1])
		return (0);
	if (str[i] == str[i + 1])
		return (1);
	return (0);
}

/*int	is_special(int c)
{
	return (c == '$' || c == '|' || c == '<' || c == '>' || c == '&'
		|| c == '~' || c == '*');
}

int	is_unhandled(int c)
{
	return (c == '`' || c == '#' || c == '\\' || c == '['
		|| c == ']' || c == '{' || c == '}' || c == ';' || c == '!');
}*/