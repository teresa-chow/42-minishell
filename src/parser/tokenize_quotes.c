/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so  <tchow-so@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 17:47:42 by tchow-so          #+#    #+#             */
/*   Updated: 2025/03/01 17:47:42 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

/*int	check_quotes(char *input)
{

	if (input && *input)
	{
		ft_strchr(input, '\'');
		ft_strrchr(input, '\'');
		ft_strchr(input, '\"');
		ft_strrchr(input, '\"');
	}
}

int	check_single_quotes()
{}

int	check_double_quotes()
{}*/

int	is_quote(int c)
{
	if (c == '\'')
		return (1);
	if (c == '\"')
		return (2);
	return (0);
}

/* Special characters: ~ * (not incl.) */
int	is_unhandled(int c)
{
	return (c == '`' || c == '#' || c == '&' || c == '\\' || c == '['
		|| c == ']' || c == '{' || c == '}' || c == ';' || c == '!');
}