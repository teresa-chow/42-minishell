/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:36:50 by tchow-so          #+#    #+#             */
/*   Updated: 2025/05/19 10:56:09 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include "../../include/execve.h"
#include "../../include/errors.h"

void	free_failed_child(t_exec_data *inf, t_data *data, t_tree_node *node)
{
	if (data->fd_copy)
	{
		close(data->fd_copy);
		data->fd_copy = -1;
	}
	close_heredoc_fds(data, NULL);
	free_arrays(inf, data, 0);
	free_env_list(data, 0, &data->env);
	reset_old_in_out(data, node);
	if (data->pipeline != NULL)
		free_pipeline(data->pipeline);
	if (data->cd_curr)
		free(data->cd_curr);
	free_ast(&data->ast_root);
}
