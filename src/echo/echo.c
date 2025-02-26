#include "../include/builtins.h"

void	echo(char **input)
{
	ft_putendl_fd(input[1], 1);
}