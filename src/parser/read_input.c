/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so  <tchow-so@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:03:35 by tchow-so          #+#    #+#             */
/*   Updated: 2025/03/04 13:26:07 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/utils.h"

void	read_input(t_data *data, t_word_lst *word_lst)
{
	char	*input;

	word_lst->word = NULL;
	input = readline("minishell> ");
	if (input && *input)
	{
		add_history(input);
		data->cmd_lst = tokenize_op(input); //TODO: handle mem_alloc err
		tokenize_w_lst(data->cmd_lst, word_lst);
	}
	else if (input)
		free(input);
}
