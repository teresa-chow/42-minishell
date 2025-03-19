/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:00:39 by tchow-so          #+#    #+#             */
/*   Updated: 2025/03/19 10:19:48 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/utils.h"

void	read_input(t_word_lst **word_lst, t_data *data)
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
			free_strarray(cmd_lst);
			data->err_code = syntax_analysis(*word_lst);
		}
	}
	if (input)
		free(input);
}
