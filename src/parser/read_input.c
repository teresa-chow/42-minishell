/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so  <tchow-so@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:00:39 by tchow-so          #+#    #+#             */
/*   Updated: 2025/03/11 15:18:16 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/utils.h"

void	read_input(t_data *data, t_word_lst *word_lst)
{
	char	*input;

	word_lst->next = NULL;
	input = readline("minishell> ");
	if (input && *input)
	{
		add_history(input);
		data->cmd_lst = tokenize_op(input); //TODO: handle mem_alloc err
		tokenize_w_lst(data->cmd_lst, word_lst);
		//syntax_analysis(word_lst);
	}
	else if (input)
		free(input);
}
