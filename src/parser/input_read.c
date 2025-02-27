/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so  <tchow-so@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:11:33 by tchow-so          #+#    #+#             */
/*   Updated: 2025/02/25 15:13:19 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/builtins.h" //tmp

void	read_input(void)
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
	//lexer -- attaches content to tokenizer
	free(input); // free memory alloc'ed by readline
}

/*
OBS.
- readline() can return NULL when the users exits
*/