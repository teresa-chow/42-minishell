#include "../include/parse.h"

void	read_input(void)
{
	char	*input;

	// readline() can return NULL when the users exits
	input = readline("user ~/Documents/42-minishell "); //placeholder text
	if (input && *input) //input not NULL
		add_history(input);
	printf("%s\n", input);
	free(input); // free memory alloc'ed by readline
}