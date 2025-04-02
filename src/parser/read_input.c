/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:00:39 by tchow-so          #+#    #+#             */
/*   Updated: 2025/04/02 11:02:19 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/utils.h"
#include "../../include/errors.h"
#include "../../include/struct.h"

#include "../../tests/test.h" //delete

static int	syntax_check(t_word_lst *word_lst, t_data *data);

void	read_input(t_tree_node **root, t_data *data)
{
	char		*input;
	char		**cmd_lst;
	t_word_lst	*word_lst;

	input = readline(get_prompt(data));
	if (input && *input)
	{
		add_history(input);
		cmd_lst = tokenize_op(input);
		if (cmd_lst)
		{
			word_lst = ft_calloc(1, sizeof(t_word_lst));
			if (!word_lst)
				return ;
			tokenize_w_lst(cmd_lst, word_lst);
			print_word_lst(cmd_lst, &word_lst); //tmp
			free_strarray(cmd_lst);
			if (syntax_check(word_lst, data) == 0)
				create_syntax_tree(word_lst, root); //if no syntax errors
			free_word_lst(&word_lst);
		}
	}
	if (input)
		free(input);
}

static int	syntax_check(t_word_lst *word_lst, t_data *data)
{
	if (syntax_analysis(word_lst) != 0)
		data->error_code = ERR_BI;
	return (data->error_code);
}
