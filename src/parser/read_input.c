/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:00:39 by tchow-so          #+#    #+#             */
/*   Updated: 2025/03/21 16:11:09 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/utils.h"
#include "../../include/errors.h"

#include "../../tests/test.h" //delete

//static void	get_prompt();
static void	syntax_check(t_word_lst *word_lst, t_data *data);

void	read_input(t_tree_node **root, t_data *data)
{
	char		*input;
	char		**cmd_lst;
	t_word_lst	*word_lst;

	input = readline("minishell> ");
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
			print_word_lst(cmd_lst, &word_lst);
			free_strarray(cmd_lst);
			syntax_check(word_lst, data);
			create_syntax_tree(word_lst, root);
			free_word_lst(&word_lst);
		}
	}
	if (input)
		free(input);
}

//static void	get_prompt()

static void	syntax_check(t_word_lst *word_lst, t_data *data)
{
	if (syntax_analysis(word_lst) != 0)
		data->error_code = ERR_BI;
	//if (check_cmd != 0)
	//	data->error_code = ERR_F;
	//if (check_cmd_syntax != 0)
	//	data->error_code = ERR;
}
