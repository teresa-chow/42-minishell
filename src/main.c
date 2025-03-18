/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:11:33 by tchow-so          #+#    #+#             */
/*   Updated: 2025/03/18 11:44:54 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"
#include "../include/errors.h"
#include "../include/utils.h"

#include "../tests/test.h" //tmp
static void	data_init(t_data *data, char **envp);

int	main(int argc, char **argv, char **envp)
{
	t_data		data; //TODO: review struct elements
	t_word_lst	*word_lst;

	(void)argc;
	(void)argv;
	data_init(&data, envp);
	while (1)
	{
		word_lst = ft_calloc(1, sizeof(t_word_lst));
		if (!word_lst)
			break;
		read_input(&word_lst);
		// print_word_lst(&word_lst); //tmp
		if (word_lst->word != NULL)
			test_builtins(&data, word_lst);
		free_word_lst(&word_lst);
	}
	//rl_clear_history();
	return (0);
}

static void	data_init(t_data *data, char **envp)
{
	ft_bzero(data, sizeof(t_data));
	// ft_bzero(, sizeof(t_word_lst));
	if (init_env_lst(envp, data) == -1)
		ft_putstr_fd("minishell: error: failed to initialize environment\n", 2);
}