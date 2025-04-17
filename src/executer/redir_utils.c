/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:46:49 by tchow-so          #+#    #+#             */
/*   Updated: 2025/04/17 11:05:06 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/execute.h"
#include "../../include/errors.h"
#include "../../include/utils.h"

void	save_old_in_out(int *old_stdin, int *old_stdout)
{
	*old_stdin = dup(STDIN_FILENO);
	*old_stdout = dup(STDOUT_FILENO);
}

void	reset_old_in_out(int old_stdin, int old_stdout)
{
	if (dup2(old_stdin, STDIN_FILENO) == -1)
	{
		perror("minishell: dup2");
		return ;
	}
	close(old_stdin);
	if (dup2(old_stdout, STDOUT_FILENO) == -1)
	{
		perror("minishell: dup2");
		return ;
	}
	close(old_stdout);
}

int redir_in_out_check(t_word *word, t_data *data)
{
	(void)data;
	while (word)
	{
		if (word->redir != NONE)
		{
			if (word->next)
			{
				if (access(word->next->word, F_OK) < 0)
				{
					no_file_or_directory(word->next->word, data);
					data->exit_status = 1;
					return (-1);
				}
				if (word->redir == OUT && access(word->next->word, W_OK) < 0)
				{
					print_fd(STDERR_FILENO, "minishell: %s: ", word->next->word);
					perror("");
					data->exit_status = 1;
					return (-1);
				}
				if (word->redir == IN && access(word->next->word, R_OK) < 0)
				{
					print_fd(STDERR_FILENO, "minishell: %s: ", word->next->word);
					perror("");
					data->exit_status = 1;
					return (-1);
				}
			}
		}
		word = word->next;
	}
	return (0);
}
