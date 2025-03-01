#include "../../include/execve.h"
#include "../../include/utils.h"
#include "../../include/parse.h"

static	char	**creat_arr(t_world_list *input)
{
	int	count;
	t_word_desc	*curr;
	char	**arr;
	int	i;

	curr = input->word->word;
	count = 0;
	while (curr)
	{
		count++;
		curr = curr->next;
	}
	arr = ft_calloc(count + 1, sizeof(t_word_desc *));
	arr[count] = 0;
	// if faill i have to free....
	curr = input->word->word;
	i = 0;
	while (curr)
	{
		arr[i++] = curr;
		curr = curr->next;
	}
	return (arr);
}

int	find_slash(char *s)
{
	while (*s)
	{
		if (*s == '/')
			return (1);
		s++;
	}
	return (0);
}

void	check_command(t_world_list *input)
{
	char	**arr;

	arr = creat_arr(input);
	if (find_slash(arr[0]))
		execve(arr[0], arr, NULL);

}