#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(int ac, char **av) {
	char	*input;
	(void)ac;
	(void)input;
	pid_t pid;
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
