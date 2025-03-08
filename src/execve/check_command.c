#include "../../include/execve.h"
#include "../../include/utils.h"
#include "../../include/parse.h"

static	char	**creat_arr(t_word_lst *input)
{
	int	count;
	t_word	*curr;
	char	**arr;
	int	i;

	curr = input->word;
	count = 0;
	while (curr)
	{
		count++;
		curr = curr->next;
	}
	arr = ft_calloc(count + 1, sizeof(t_word *));
	arr[count] = 0;
	// if faill i have to free....
	curr = input->word;
	i = 0;
	while (curr)
	{
		arr[i++] = curr->word;
		curr = curr->next;
	}
	return (arr);
}

static int	find_slash(char *s)
{
	while (*s)
	{
		if (*s == '/')
			return (1);
		s++;
	}
	return (0);
}
void	check_command(t_word_lst *input, t_env_node *env_lst)
{
	char	**arr;
	pid_t	pid;

	(void)env_lst;
	arr = creat_arr(input);
	if (find_slash(arr[0]))
	{
		pid = fork();
		/*TODO: get path and then access*/
		if (pid == 0)
		{
			if (execve(arr[0], arr, NULL) == -1)
				perror("error");
		}
		else
			wait(NULL);
	}
}