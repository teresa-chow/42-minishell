/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so  <tchow-so@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:11:33 by tchow-so          #+#    #+#             */
/*   Updated: 2025/02/26 10:21:05 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"
#include "../include/builtins.h"

void	read_input(void)
{
	char	*input;
	char	**tokens;

	input = readline("minishell> ");
	if (input && *input)
		add_history(input);
	tokens = tokenizer(input);
	echo(tokens);
	//lexer -- attaches content to tokenizer
	free(input); // free memory alloc'ed by readline
}

/*
OBS.
- readline() can return NULL when the users exits
*/
