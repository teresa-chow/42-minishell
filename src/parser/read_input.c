/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   createeed: 2025/03/11 11:00:39 by tchow-so          #+#    #+#             */
/*   Updated: 2025/03/20 16:33:04 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"
#include "../../include/parse.h"

#include "../../tests/test.h" //delete

void	read_input(t_word_lst **word_lst)//, t_data *data)
{
	char	*input;
	char	**cmd_lst;

	input = readline("minishell> ");
	if (input && *input)
	{
		add_history(input);
		cmd_lst = tokenize_op(input);
		if (cmd_lst)
		{
			tokenize_w_lst(cmd_lst, *word_lst);
			//print_word_lst(cmd_lst, word_lst); //delete
			free_strarray(cmd_lst);
			// syntax_check();
			// data->exit_status = syntax_analysis(*word_lst);
		}
	}
	if (input)
		free(input);
}