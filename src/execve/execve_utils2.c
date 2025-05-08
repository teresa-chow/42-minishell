/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:36:50 by tchow-so          #+#    #+#             */
/*   Updated: 2025/05/08 17:06:17 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include "../../include/execve.h"
#include "../../include/errors.h"

void	free_failed_child(t_exec_data *inf, t_data *data, t_tree_node *node)
{
	free_arrays(inf, data, 0);
	free_env_list(data, 0, &data->env);
	close_heredoc_fds(data, NULL);
	if (data->pipeline != NULL)
		free_pipeline(data->pipeline);
	reset_old_in_out(data, node);
	free_ast(&data->ast_root);
}
