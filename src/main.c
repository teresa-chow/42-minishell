#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(int ac, char **av)
{
	char	*env_var;
	char	*input;
	pid_t pid;

	(void)ac;
	env_var = getenv("PATH");
	printf("PATH: %s\n", env_var);
	while (1)
	{
		input = readline("minishell>");
		pid = fork();
		if (pid == 0)
		{
			printf("fodasse\n");
			execve(input, av + 1, NULL);
		}
		else
		wait(NULL);
	}
    return 0;
}
