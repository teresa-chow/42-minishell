#include "test.h"

/*****************************************************************************\
|                            BUILTINS TEST FUNCTIONS                          |
\*****************************************************************************/
void	test_builtins(t_word_lst *word_lst, t_env_node **env_lst)
{
	if (ft_strcmp(word_lst->word->word, "echo") == 0)
		echo(word_lst->word);
	else if (ft_strcmp(word_lst->word->word, "cd") == 0)
		cd(word_lst->word);
	else if (ft_strcmp(word_lst->word->word, "pwd") == 0)
		pwd();
	else if (ft_strcmp(word_lst->word->word ,"export") == 0)
		export(word_lst->word, env_lst);
	else if (ft_strcmp(word_lst->word->word ,"unset") == 0)
		unset(env_lst, word_lst->word->next);
	else
		check_command(word_lst, *env_lst); // change env_parameter to an bidimensional array
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