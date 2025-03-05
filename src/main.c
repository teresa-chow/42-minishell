/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:11:33 by tchow-so          #+#    #+#             */
/*   Updated: 2025/02/27 14:09:36 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"
#include "../include/builtins.h"
#include "../include/execve.h"
#include "../include/utils.h"

static void	test_builtins(t_word_lst *word_lst, t_env_node **env_lst);

int	main(int argc, char **argv, char **envp)
{
	t_word_lst	word_lst;
	t_env_node	*env_lst;

	(void)argc;
	(void)argv;
	env_lst = NULL;
	if (init_env_lst(envp, &env_lst) == 0)
		ft_putstr_fd("Error\n", 2); //improve this error situation 
	while (1)
	{
		read_input(envp, &word_lst);
		if (word_lst.word != NULL)
			test_builtins(&word_lst, &env_lst);
	}
	return (0);
}

/* temp test function: echo, cd, pwd */
static void	test_builtins(t_word_lst *word_lst, t_env_node **env_lst)
{
	if (ft_strcmp(word_lst->word->word, "echo") == 0)
		echo(word_lst->word);
	else if (ft_strcmp(word_lst->word->word, "cd") == 0)
		cd(word_lst->word);
	else if (ft_strcmp(word_lst->word->word, "pwd") == 0)
		pwd();
	else if (ft_strcmp(word_lst->word->word ,"export") == 0)
		export(word_lst->word , *env_lst);
	else if (ft_strcmp(word_lst->word->word ,"unset") == 0)
		unset(env_lst, word_lst->word->next);
	else
		check_command(word_lst, *env_lst); // change env_parameter to an bidimensional array
}
