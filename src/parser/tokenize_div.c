/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_div.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:09:23 by tchow-so          #+#    #+#             */
/*   Updated: 2025/03/21 14:48:00 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO: handle memory alloc errors (returns -1)

#include "../../include/parse.h"
#include "../../include/utils.h"

/* Tokenization (2): split words (divide by whitespaces) */
void	tokenize_w_lst(char **cmd_lst, t_word_lst *word_lst)
{
	t_word		*word_tmp;
	int			i;
	int			j;

	i = 0;
	while (cmd_lst[i])
	{
		j = 0;
		word_tmp = NULL;
		while (cmd_lst[i][j] != '\0')
		{
			handle_parentheses(cmd_lst[i], &j, &word_lst, &word_tmp);
			handle_redirection(cmd_lst[i], &j, &word_lst, &word_tmp);
			handle_other(cmd_lst[i], &j, &word_lst, &word_tmp);
			handle_quote(cmd_lst[i], &j, &word_lst, &word_tmp);
			while (is_delimiter(cmd_lst[i][j]))
				j++;
		}
		i++;
		if (cmd_lst[i])
			add_word_lst(&word_lst);
	}
	word_tmp = NULL;
}
