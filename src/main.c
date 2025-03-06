/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:11:33 by tchow-so          #+#    #+#             */
/*   Updated: 2025/03/06 17:41:32 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"
#include "../include/builtins.h"
#include "../include/execve.h"
#include "../include/utils.h"

#include "../tests/test.h" //tmp

int	main(int argc, char **argv, char **envp)
{
	t_data		data;
	t_word_lst	word_lst;
	t_env_node	*env_lst;

	(void)argc;
	(void)envp;
	(void)argv;
	envp = NULL;
	env_lst = NULL;
	data.envp = envp;
	if (init_env_lst(data.envp, &env_lst) == 0)
		ft_putstr_fd("minishell: error: failed to initialize environment\n", 2); //improve this error situation 
	while (1)
	{
		read_input(&data, &word_lst);
		    print_word_lst(&data, &word_lst); //tmp
		if (word_lst.word != NULL)
			test_builtins(&word_lst, &env_lst);
	}
	//rl_clear_history();
	return (0);
}
