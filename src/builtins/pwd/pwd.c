#include "../../../include/builtins.h"

void	pwd(void)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	printf ("%s\n", buf);
	free(buf);
}