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
			if (cmd_lst[i][j] == '(')
			{
				handle_parentheses(cmd_lst[i], j, word_lst);
				break ;
			}
			if (!is_delimiter(cmd_lst[i][j]) && !is_quote(cmd_lst[i][j]))
				handle_other(cmd_lst[i], &j, &word_lst, &word_tmp);
			if (is_quote(cmd_lst[i][j])) // TODO: unclosed quotes
				handle_quote(cmd_lst[i], &j, &word_lst, &word_tmp);
			else
				while (is_delimiter(cmd_lst[i][j]))
					j++;
		}
		i++;
		if (cmd_lst[i])
			add_word_lst(&word_lst);
	}
	free(word_tmp);

	return (0);
}

int handle_parentheses(char *cmd, int start, t_word_lst *word_lst)
{
	int	len;
	int i;

	i = 0;
	len = (ft_strlen(cmd) - start) + 1;
	word_lst->word = ft_calloc(1, sizeof(t_word));
	word_lst->word->word = malloc(len * sizeof(char));
	while (cmd[start] && cmd[start] != ')')
		word_lst->word->word[i++] = cmd[start++];
	if (cmd[start] && cmd[start] == ')')
		word_lst->word->word[i++] = cmd[start++];
	word_lst->word->word[i] = '\0';
	return (start);
}