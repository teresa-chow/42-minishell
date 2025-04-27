/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:08:53 by tchow-so          #+#    #+#             */
/*   Updated: 2025/04/27 00:14:05 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/builtins.h"
#include "../../include/execve.h"
#include "../../include/errors.h"

int	cd_arg_check(t_word *word, t_data *data)
{
	if (word->next && word->next->next
	&& word->next->next->redir == NONE)
	{
		cd_error(NULL, data, 0);
		return (0);
	}
	return (1);
}

void	exec_child(t_data *data, t_word *word)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid < 0)
	{
		perror("minishell");
		return ;
	}
	else if (pid == 0)
		exec(data, word);
	else
		waitpid(pid, &status, 0);
	data->exit_status = WEXITSTATUS(status);
}