/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:00:39 by tchow-so          #+#    #+#             */
/*   Updated: 2025/03/19 14:11:16 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

/*****************************************************************************\
|                            BUILTINS TEST FUNCTIONS                          |
\*****************************************************************************/

int	find_expansion(char *arg, int *has_quotes)
{
	while (*arg)
	{
		if (*arg == '"')
			*has_quotes = 1;
		if (*arg == '$' && *(arg + 1))
			return (1);
		arg++;
	}
	return (0);
}

void	split_val(t_word *word, char *val, t_word_lst *word_lst)
{
	char	**result;
	char	*cmd;
	t_word	*tmp;

	(void)result;
	(void)cmd;
	(void)val;
	cmd = ft_strdup(word->word);
	free_words(&word);
	result = tokenize_op(val);
	tokenize_w_lst(result, word_lst);
	tmp = ft_calloc(sizeof(t_word), sizeof(char));
	tmp->word = cmd;
	tmp->next = word_lst->word;
	word_lst->word = tmp;
}

void	expand(t_word *word, int *has_quotes, t_data *data, t_word_lst *word_lst)
{
	char	*param;
	t_word	*tmp;
	t_env_node	*param_val;

	(void)has_quotes;
	(void)param_val;
	tmp = NULL;
	tmp = word->next;
	param = NULL;
	param = ft_strchr(tmp->word, '$') + 1;
	param_val = get_var(data->env, param);
	if (!*has_quotes && param_val)
	{
		split_val(word, param_val->val, word_lst);
	}
	if (param_val)
	{
		free(word->word);
		word->word = param_val->val;
	}

}

void	check_special_cases(t_word *word, t_data *data, t_word_lst *word_lst)
{
	int	has_quotes;
	t_word	*tmp;
	t_env_node	*delete;

	delete = get_var(data->env, "ZZ");
	delete->val = "hello       world";

	tmp = word->next;
	has_quotes = 0;
	while (tmp)
	{
		if (find_expansion(tmp->word, &has_quotes))
		{
			expand(word, &has_quotes, data, word_lst);
		}
		word = word->next;
	}
}


void	test_builtins(t_data *data, t_word_lst **word_lst, int *i)
{
	if (ft_strcmp((*word_lst)->word->word, "echo") == 0)
	{
		check_special_cases((*word_lst)->word, data, *word_lst);
		echo((*word_lst)->word, data);
	}
	else if (ft_strcmp((*word_lst)->word->word, "cd") == 0)
		cd((*word_lst)->word, data);
	else if (ft_strcmp((*word_lst)->word->word, "pwd") == 0)
		pwd(data);	
	else if (ft_strcmp((*word_lst)->word->word ,"export") == 0)
		export(data, (*word_lst)->word);
	else if (ft_strcmp((*word_lst)->word->word,"unset") == 0)
		unset(data, (*word_lst)->word->next);
	else if (ft_strcmp((*word_lst)->word->word,"env") == 0)
		env_cmd(data->env, data);
	else if (!ft_strcmp((*word_lst)->word->word, "exit"))
		check_exit_args(data, word_lst, i); /// in the future, the argument is the tree and then
						    /// we have to free the tree
	else
		exec(data, (*word_lst)->word);
}
/*****************************************************************************\
|                             PARSER TEST FUNCTIONS                           |
\*****************************************************************************/
void	print_word_lst(char **cmd_lst, t_word_lst **word_lst)
{
	int			i = 0;
	int			cmd_n = 0;
	t_word		*word_ptr;
	t_word_lst	*lst_ptr;

	lst_ptr = *word_lst;
	word_ptr = (*word_lst)->word;
	if (cmd_lst == NULL)
		return ;
	ft_printf("--------------------------------------\n");
	while (cmd_lst[i])
	{
		ft_printf("cmd: %s\n", cmd_lst[i]);
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