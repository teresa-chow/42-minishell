/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:11:33 by tchow-so          #+#    #+#             */
/*   Updated: 2025/05/08 15:25:56 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"
#include "../include/execute.h"
#include "../include/errors.h"
#include "../include/utils.h"

static void	init_prog(t_data *data, char **envp);
static void	data_init(t_data *data, char **envp);
static void	processing_loop(t_data *data, bool env);

int	g_global;

int	main(int argc, char **argv, char **envp)
{
	t_data		data;
	bool		env;

	(void)argc;
	(void)argv;
	env = 1;
	if (!*envp)
		env = 0;
	g_global = 0;
	init_prog(&data, envp);
	while (data.status)
		processing_loop(&data, env);
	rl_clear_history();
	return (data.exit_status);
}

static void	init_prog(t_data *data, char **envp)
{
	data_init(data, envp);
	set_signals();
	signal (SIGINT, handle_signal);
}

static void	data_init(t_data *data, char **envp)
{
	t_env_node	*var;

	ft_bzero(data, sizeof(t_data));
	if (init_env_lst(envp, data) == -1)
		ft_putstr_fd("minishell: error: failed to initialize environment\n",
			STDERR_FILENO);
	var = ft_getenv(data->env, "HOME");
	if (var)
		data->env_home_var = var->val;
	else
		data->no_home = true;
	data->status = 1;
}

static void	processing_loop(t_data *data, bool env)
{
	t_tree_node	*root;

	root = ft_calloc(1, sizeof(t_tree_node));
	if (!root)
	{
		free_env_list(data, 1, &data->env);
		return ;
	}
	read_input(&root, data, env);
	if (g_global == SIGINT)
		data->exit_status = ERR_INT;
	if (root->word)
	{
		if (!search_heredoc(data, &root))
			ast_depth_search(data, &root, 0);
		close_heredoc_fds(data, NULL);
	}
	reset_mem(data, &root);
}
