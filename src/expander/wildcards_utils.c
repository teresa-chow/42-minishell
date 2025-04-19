/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42porto.com>    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-19 14:35:44 by carlaugu          #+#    #+#             */
/*   Updated: 2025-04-19 14:35:44 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expand.h"

char	*get_last_ast(char *s)
{
	char	*ast;
	while (*s)
	{
		if (*s == '*')
			ast = s;
		s++;
	}
	return (ast);
}

char	*next_ast(char *s)
{
	while (*s)
	{
		if (*s == '*')
			return (s);
		s++;
	}
	return (NULL);
}

char	*find_first_no_ast(char *s)
{
	while (*s)
	{
		if (*s != '*')
			return (s);
		s++;
	}
	return (s);
}