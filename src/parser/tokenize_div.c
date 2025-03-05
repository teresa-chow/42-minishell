/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_div.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so  <tchow-so@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:09:23 by tchow-so          #+#    #+#             */
/*   Updated: 2025/03/01 11:25:31 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TO DO: handle memory alloc errors (returns -1)

#include "../../include/parse.h"

/* Tokenization (2): split words (divide by whitespaces) */
int	tokenize_w_lst(char **cmd_lst, t_word_lst *word_lst)
{
	t_word		*word_desc;
	int			i;
	int			j;

	i = 0;
	word_desc = NULL;
	while (cmd_lst[i])
	{
		j = 0;
		while (cmd_lst[i][j] != '\0')
		{
			if (!is_delimiter(cmd_lst[i][j]) && !is_quote(cmd_lst[i][j]))
				handle_other(cmd_lst[i], &j, word_lst, &word_desc);
			if (is_quote(cmd_lst[i][j]))
				handle_quote(cmd_lst[i], &j, word_lst, &word_desc);
			else
			{
				while (is_delimiter(cmd_lst[i][j]))
					j++;
			}
		}
		i++;
	}
	word_lst->next = NULL; // future fix: multiple commands
	return (0);
}
