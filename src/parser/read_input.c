/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:00:39 by tchow-so          #+#    #+#             */
/*   Updated: 2025/04/10 17:19:31 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"
#include "../../include/errors.h"
#include "../../include/struct.h"

static void	process_cmd_lst(char **cmd_lst, t_data *data, t_tree_node **root);
static int	syntax_check(t_word_lst *word_lst, t_data *data);

void	read_input(t_tree_node **root, t_data *data)
{
	char		*input;
	char		*prompt;
	char		**cmd_lst;

	prompt = get_prompt(data);
	input = readline(prompt);
	if (input && *input)
	{
		add_history(input);
		cmd_lst = tokenize_op(input);
		if (cmd_lst)
			process_cmd_lst(cmd_lst, data, root);
	}
	free(prompt);
	if (input)
		free(input);
}

static void	process_cmd_lst(char **cmd_lst, t_data *data, t_tree_node **root)
{
	t_word_lst	*word_lst;

	word_lst = ft_calloc(1, sizeof(t_word_lst));
	if (!word_lst)
	{
		free_strarray(cmd_lst);
		return ;
	}
	tokenize_w_lst(cmd_lst, word_lst);
	free_strarray(cmd_lst);
	if (syntax_check(word_lst, data) == 0)
	{
		create_syntax_tree(word_lst, NULL, 0, root);
		free_word_lst(&word_lst);
	}
	else
		free_w_lst_words(&word_lst);
}

static int	syntax_check(t_word_lst *word_lst, t_data *data)
{
	if (syntax_analysis(word_lst) != 0)
	{
		data->exit_status = ERR_BI;
		return (ERR_BI);
	}
	return (0);
}
