/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:11:33 by tchow-so          #+#    #+#             */
/*   Updated: 2025/03/11 13:06:55 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"
#include "../include/builtins.h"
#include "../include/utils.h"
#include "../include/execve.h"


//if we press enter when wait an input, we have seg fault  <<<<---------------------------------
#include "../tests/test.h" //tmp

int	main(int argc, char **argv, char **envp)
{
	t_data		data;
	t_word_lst	word_lst;
	t_env_node	*env_lst;

	(void)argc;
	(void)argv;
	ft_bzero(&data, sizeof(t_data));
	ft_bzero(&word_lst, sizeof(t_word_lst));
	ft_bzero(&env_lst, sizeof(t_env_node));
	env_lst = NULL;
	data.envp = envp;
	if (init_env_lst(data.envp, &env_lst) == -1)
		ft_putstr_fd("minishell: error: failed to initialize environment\n", 2);
	while (1)
	{
		read_input(&data, &word_lst);
		    print_word_lst(&data, &word_lst); //tmp
		if (word_lst.word != NULL)
			test_builtins(&word_lst, &env_lst);
		// free_word_lst(&word_lst); // this will try free a static structure like word_lst and
					//   will fail. We have to create a pointer to struct
	}
	//rl_clear_history();
	return (0);
}
