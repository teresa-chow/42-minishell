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

#include "../../include/parse.h"
#include "../../include/utils.h"

#include "../../tests/test.h" //delete

int	check_export_arg_sintax(char *s)
{
	while (*s)
	{
		if (*s == '+' && *(s + 1) != '=')
		{
			wrong_export_sintax(s); ///////////////////and free this node
			return (0);                
		}

	}
}

void	check_export_args(t_word *word)
{
	while (word)
	{
		check_syntax(word->word);
	}
}

int	cmd_and_args_check(t_data *data, t_word_lst **word_lst)
{
	while (word_lst)
	{
		if (ft_strcmp((*word_lst)->word->word, "echo") == 0)
			return (0);
		else if (ft_strcmp((*word_lst)->word->word, "cd") == 0)
			return (0);
		else if (ft_strcmp((*word_lst)->word->word, "pwd") == 0)
			return (0);
		else if (ft_strcmp((*word_lst)->word->word ,"export") == 0)
		{
			check_export_args((*word_lst)->word);
		}	
		// else if (ft_strcmp((*word_lst)->word->word,"unset") == 0)
			
		// else if (ft_strcmp((*word_lst)->word->word,"env") == 0)
			
		// else
		// 	exec(data, word_lst->word);
	}
}

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
			// if (!cmd_and_args_check(data, word_lst))
			// 	printf("\n");	// call createee_syntax_tree;
			// data->exit_status = syntax_analysis(*word_lst);
		}
	}
	if (input)
		free(input);
}
