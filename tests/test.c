#include "test.h"

/*****************************************************************************\
|                            BUILTINS TEST FUNCTIONS                          |
\*****************************************************************************/
void	test_builtins(t_data *data)
{
	if (ft_strcmp(data->word_lst.word->word, "echo") == 0)
		echo(data->word_lst.word);


	else if (ft_strcmp(data->word_lst.word->word, "cd") == 0)
		cd(data->word_lst.word);
	else if (ft_strcmp(data->word_lst.word->word, "pwd") == 0)
		pwd();	
	else if (ft_strcmp(data->word_lst.word->word ,"export") == 0)
		export(data);
	else if (ft_strcmp(data->word_lst.word->word,"unset") == 0)
		unset(data);
	else if (ft_strcmp(data->word_lst.word->word,"env") == 0)
		env_cmd(data->env);
	else
		exec(data->env, data->word_lst.word, data);
}

/*****************************************************************************\
|                             PARSER TEST FUNCTIONS                           |
\*****************************************************************************/
void	print_word_lst(t_data *data, t_word_lst *word_lst)
{
	int			i = 0;
	int			cmd_n = 0;
	t_word		*word_ptr;
	t_word_lst	*lst_ptr;

	lst_ptr = word_lst;
	word_ptr = word_lst->word;
	ft_printf("--------------------------------------\n");
	while (data->cmd_lst[i])
	{
		ft_printf("cmd: %s\n", data->cmd_lst[i]);
		i++;
	}
	ft_printf("--------------------------------------\n");
	while (lst_ptr)
	{
		ft_printf("## cmd no.: %d\n", cmd_n);
		word_ptr = lst_ptr->word;
		while (word_ptr)
		{
			ft_printf("word: %s\n", word_ptr->word);
			word_ptr = word_ptr->next;
		}
		lst_ptr = lst_ptr->next;
		cmd_n++;
		ft_printf("------------------\n");
	}
	ft_printf("\n\n--------------------------------------\n");
}