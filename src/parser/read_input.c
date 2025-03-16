/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:03:35 by tchow-so          #+#    #+#             */
/*   Updated: 2025/03/06 15:48:14 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/utils.h"

void	read_input(t_data *data)
{
	char	*input;

	data->word_lst.next = NULL;
	input = readline("minishell> ");
	if (input && *input)
	{
		add_history(input);
		data->cmd_lst = tokenize_op(input); //TODO: handle mem_alloc err
		tokenize_w_lst(data->cmd_lst, &data->word_lst);
	}
	else if (input)
		free(input);
}
