/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:11:33 by tchow-so          #+#    #+#             */
/*   Updated: 2025/03/12 11:18:20 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"
#include "../include/error.h"
#include "../include/utils.h"

//if we press enter when wait an input, we have seg fault  <<<<---------------------------------
#include "../tests/test.h" //tmp

// we create a env_path copy but if we unset PATH what should happen??? ---------------------------------------------

void	data_init(t_data *data, char **envp)
{
	ft_bzero(data, sizeof(t_data));
	// ft_bzero(, sizeof(t_word_lst));
	if (init_env_lst(envp, data) == -1)
		ft_putstr_fd("minishell: error: failed to initialize environment\n", 2);
}
int	main(int argc, char **argv, char **envp)
{
	t_data		data;

	(void)argc;
	(void)argv;
	data_init(&data, envp);
	while (1)
	{
		read_input(&data);
		//     print_word_lst(&data, &word_lst); //tmp
		if (data.word_lst.word != NULL)
			test_builtins(&data);
		// free_word_lst(&word_lst); // this will try free a static structure like word_lst and
					//   will fail. We have to create a pointer to struct
	}
	//rl_clear_history();
	return (0);
}
