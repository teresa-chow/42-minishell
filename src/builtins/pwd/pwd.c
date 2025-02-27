#include "../../../include/builtins.h"

void	pwd(char **input)
{
	(void)input;
	char	*buf;

	buf = getcwd(NULL, 0);
	printf ("%s\n", buf);
	free(buf);
}