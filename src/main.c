/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:11:33 by tchow-so          #+#    #+#             */
/*   Updated: 2025/04/08 14:21:26 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"
#include "../include/errors.h"
#include "../include/utils.h"

static void	data_init(t_data *data, char **envp);
static void	reset_old_data(t_data *data);

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
		/*if (!root)
		{
			free_env_list(&data, 1, &data.env);
			break;
		}*/
		read_input(&root, &data);
		if (root->word)
			ast_depth_search(&data, &root, &i);
		if (i)
			reset_old_data(&data); //TODO: refactor to include tree (?)
	}
	rl_clear_history();
	return (data.exit_status);
}

static void	data_init(t_data *data, char **envp)
{
	ft_bzero(data, sizeof(t_data));
	if (init_env_lst(envp, data) == -1)
		ft_putstr_fd("minishell: error: failed to initialize environment\n", 2);
}

//TODO: move to mem_utils (adapted, doesn't take word_lst)
static	void	reset_old_data(t_data *data)
{
	// here we have to free t_word
	data->exp->export_cmd = false;
	data->exp->export_after_equal = false;
	free(data->home_path);
	data->home_path = NULL;
	free(data->exp);
	data->exp = NULL;
}	