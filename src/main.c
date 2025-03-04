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

//static void	test_builtins(t_word_lst *word_lst, char **envp);

int	main(int argc, char **argv, char **envp)
{
	t_data		data;
	t_word_lst	word_lst;

	(void)argc;
	(void)argv;
	while (1)
	{
		data.envp = envp;
		read_input(&data, &word_lst);
		//if (word_lst.word != NULL)
		//	test_builtins(&word_lst, data.envp);
	}
	return (0);
}

/* temp test function: echo, cd, pwd */
/*static void	test_builtins(t_word_lst *word_lst, char **envp)
{
	if (ft_strncmp(word_lst->word->word, "echo", 4) == 0)
		echo(word_lst->word);
	else if (ft_strncmp(word_lst->word->word, "cd", 2) == 0)
		cd(word_lst->word);
	else if (ft_strncmp(word_lst->word->word, "pwd", 3) == 0)
		pwd();
	else
		get_path(envp);
}*/
