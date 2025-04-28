/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:11:33 by tchow-so          #+#    #+#             */
/*   Updated: 2025/04/24 12:27:37 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"
#include "../include/execute.h"
#include "../include/errors.h"
#include "../include/utils.h"

static void	data_init(t_data *data, char **envp);
int	global;

int	main(int argc, char **argv, char **envp)
{
	t_data		data;
	t_tree_node	*root;
	int	i;
	
	(void)argc;
	(void)argv;
	i = 1;
	data_init(&data, envp);
	set_signals(&data);
	signal (SIGINT, handle_signal);
	while (i)
	{
		root = ft_calloc(1, sizeof(t_tree_node));
		if (!root)
		{
			free_env_list(&data, 1, &data.env);
			break;
		}
		read_input(&root, &data, &i);
		if (root->word)
			ast_depth_search(&data, &root, &i);
		reset_mem(&data, &root, i);
	}
	rl_clear_history();
	return (data.exit_status);
}

static void	data_init(t_data *data, char **envp)
{
	t_env_node	*var;

	ft_bzero(data, sizeof(t_data));
	data->i = -1;
	if (init_env_lst(envp, data) == -1)
		ft_putstr_fd("minishell: error: failed to init env\n", 2);
	var = ft_getenv(data->env, "HOME");
	if (var)
		data->env_home_var = var->val;
	else
		data->no_home = true;
}
