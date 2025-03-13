/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:11:33 by tchow-so          #+#    #+#             */
/*   Updated: 2025/03/11 10:47:54 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"
#include "../include/builtins.h"
#include "../include/execve.h"
#include "../include/errors.h"
#include "../include/utils.h"

#include "../tests/test.h" //tmp

int	main(int argc, char **argv, char **envp)
{
	//t_data		data; //TODO: review struct elements
	t_word_lst	*word_lst;
	//t_env_node	*env_lst;

	(void)argc;
	(void)argv;
	//ft_bzero(&data, sizeof(t_data)); //ft_bzero(&env_lst, sizeof(t_env_node));
	//env_lst = NULL;
	//if (!init_env_lst(envp, &env_lst)) //TODO: handle with empty env like bash
	//	ft_putstr_fd("minishell: error: failed to initialize environment\n", 2);
	while (1)
	{
		word_lst = ft_calloc(1, sizeof(t_word_lst));
		if (!word_lst)
			break ;
		read_input(&word_lst);
		print_word_lst(&word_lst); //tmp
		//if (word_lst->word != NULL)
		//	test_builtins(&word_lst, &env_lst);
		free_word_lst(&word_lst);
	}
	//rl_clear_history();
	return (0);
}
