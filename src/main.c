/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:11:33 by tchow-so          #+#    #+#             */
/*   Updated: 2025/04/10 17:15:35 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"
#include "../include/errors.h"
#include "../include/utils.h"

static void	data_init(t_data *data, char **envp);
static void	reset_mem(t_data *data, t_tree_node **root, int i);

int	main(int argc, char **argv, char **envp)
{
	t_data		data;
	t_tree_node	*root;
	int	i;

	(void)argc;
	(void)argv;
	i = 1;
	data_init(&data, envp);
	while (i)
	{
		root = ft_calloc(1, sizeof(t_tree_node));
		if (!root)
		{
			free_env_list(&data, 1, &data.env);
			break;
		}
		read_input(&root, &data);
		if (root->word)
			ast_depth_search(&data, &root, &i);
		reset_mem(&data, &root, i);
		free(root);
	}
	rl_clear_history();
	return (data.exit_status);
}

static void	data_init(t_data *data, char **envp)
{
	t_env_node	*var;

	ft_bzero(data, sizeof(t_data));
	if (init_env_lst(envp, data) == -1)
		ft_putstr_fd("minishell: error: failed to initialize environment\n", 2);
	var = ft_getenv(data->env, "HOME");
	if (var)
		data->env_home_var = var->val;
}

//TODO: move to mem_utils
static	void	reset_mem(t_data *data, t_tree_node **root, int i)
{
	t_env_node	*var;

	data->exp->export_cmd = false;
	data->exp->export_after_equal = false;
	free(data->exp);
	data->exp = NULL;
	free_ast(root);
	if(data->no_home)
		free(data->env_home_var);
	data->env_home_var = NULL;
	var = ft_getenv(data->env, "HOME");
	if (var)
		data->env_home_var = var->val;
	if (!i)
		free_env_list(data, 0, &data->env);
}
