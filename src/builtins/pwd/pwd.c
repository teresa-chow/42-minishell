#include "../../../include/builtins.h"

void	pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		perror("minishell");
	else
		ft_printf ("%s\n", path);
	free(path);
}