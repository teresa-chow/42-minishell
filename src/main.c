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

#include "../tests/test.h" //tmp

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
		print_word_lst(&data, &word_lst); //tmp
		//if (word_lst.word != NULL)
		//	test_builtins(&word_lst, data.envp);
	}
	//rl_clear_history();
	return (0);
}
