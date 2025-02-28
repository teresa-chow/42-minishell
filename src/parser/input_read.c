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
#include "../../include/builtins.h" //tmp

void	read_input(char **envp)
{
	char	*input;
	char	**tokens;

	input = readline("minishell> ");
	if (input && *input)
		add_history(input);
	tokens = w_token(input);
	if (ft_strncmp(tokens[0], "echo", 4) == 0)
		echo(tokens);  //// this is to test with echo
	else if (ft_strncmp(tokens[0], "cd", 2) == 0)
		cd(tokens); ///// this is to test cd
	else if (ft_strncmp(tokens[0], "pwd", 3) == 0)
		pwd(tokens);
	else
		get_path(envp);
	//lexer -- attaches content to tokenizer
	free(input); // free memory alloc'ed by readline
}

/*
OBS.
- readline() can return NULL when the users exits
*/