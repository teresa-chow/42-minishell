#include "test.h"

/*****************************************************************************\
|                            BUILTINS TEST FUNCTIONS                          |
\*****************************************************************************/
void	test_builtins(t_word_lst *word_lst, char **envp)
{
	if (ft_strncmp(word_lst->word->word, "echo", 4) == 0)
		echo(word_lst->word);
	else if (ft_strncmp(word_lst->word->word, "cd", 2) == 0)
		cd(word_lst->word);
	else if (ft_strncmp(word_lst->word->word, "pwd", 3) == 0)
		pwd();
	else
		get_path(envp);
}

/*****************************************************************************\
|                             PARSER TEST FUNCTIONS                           |
\*****************************************************************************/
void	print_word_lst(t_data *data, t_word_lst *word_lst)
{
	int			i = 0;
	t_word		*word_ptr;
	t_word_lst	*lst_ptr;

	lst_ptr = word_lst;
	word_ptr = word_lst->word;
	while (data->cmd_lst[i])
	{
		ft_printf("cmd: %s\n", data->cmd_lst[i]);
		i++;
	}
	while (lst_ptr)
	{
		while (word_ptr)
		{
			ft_printf("word: %s\n", word_ptr->word);
			word_ptr = word_ptr->next;
		}
		lst_ptr = lst_ptr->next;
	}
}