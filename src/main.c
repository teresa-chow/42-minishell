/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:11:33 by tchow-so          #+#    #+#             */
/*   Updated: 2025/04/10 11:06:11 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"
#include "../include/errors.h"
#include "../include/utils.h"

static void	data_init(t_data *data, char **envp);
static void	free_old_mem(t_data *data, t_tree_node **root, int i);

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
		free_old_mem(&data, &root, i);
		free(root);
	}
	rl_clear_history();
	return (data.exit_status);
}

static void	data_init(t_data *data, char **envp)
{
	ft_bzero(data, sizeof(t_data)); //is resetting exit satus -- static ?
	if (init_env_lst(envp, data) == -1)
		ft_putstr_fd("minishell: error: failed to initialize environment\n", 2);
}

//TODO: move to mem_utils (adapted, doesn't take word_lst)
static	void	free_old_mem(t_data *data, t_tree_node **root, int i)
{
	if (!i)
		free_env_list(data, 0, &data->env);
	if (*root)
		free_ast(root);
	if (data->home_path)
		free(data->home_path);
	data->home_path = NULL;
}	