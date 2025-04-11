/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:46:49 by tchow-so          #+#    #+#             */
/*   Updated: 2025/04/11 15:55:28 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/execute.h"
#include "../../include/utils.h"

void	save_old_stdout(int *old_stdout)
{
	*old_stdout = dup(STDOUT_FILENO);
}

void	reset_old_stdout(int old_stdout)
{
	if (dup2(old_stdout, STDOUT_FILENO) == -1)
	{
		perror("minishell: dup2");
		return ;
	}
	close(old_stdout);
}

