/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:11:33 by tchow-so          #+#    #+#             */
/*   Updated: 2025/02/27 14:10:03 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

void	read_input(char **envp, t_word_lst *word_lst)
{
	char	*input;

	(void)envp;
	word_lst->word = NULL;
	input = readline("minishell> ");
	if (input && *input)
	{
		add_history(input);
		tokenize_w_lst(input, word_lst);
	}
	else if (input)
		free(input);
}