/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:46:49 by tchow-so          #+#    #+#             */
/*   Updated: 2025/04/16 17:43:04 by carlaugu         ###   ########.fr       */
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

int	check_permission(t_word *word, t_data *data)
{
	if ((word->redir == OUT  || word->redir == APPEND) 
		&& access(word->next->word, W_OK) == -1)
	{
		print_fd(STDERR_FILENO, "minishell: %s: ", word->next->word);
		perror("");
		data->exit_status = 1;
		return (-1);
	}
	if (word->redir == IN && access(word->next->word, R_OK) == -1)
	{
		print_fd(STDERR_FILENO, "minishell: %s: ", word->next->word);
		perror("");
		data->exit_status = 1;
		return (-1);
	}
	return (0);
}

int	handle_redir(t_data *data, t_word *word)
{
	if (data->redir_in)
		redir_in(word, data);
	else if (data->redir_out)
		redir_out(data, word);
	data->redir_in = false;
	data->redir_out = false;
}

int redir_in_out_check(t_word *word, t_data *data)
{
	t_word	*tmp;

	tmp = word;
	while (tmp)
	{
		if (tmp->redir != NONE && tmp->next)
		{
			if (!access(tmp->next->word, F_OK))
			{
				if (check_permission(tmp, data) == -1)
					return (-1);
				if (tmp->redir == IN)
					data->redir_in = true;
				else if (tmp->redir == OUT || tmp->redir == APPEND)
					data->redir_out = true;
			}
			else
				return (no_file_or_dir(tmp->next->word, data, 1), 1);
		}
		tmp = tmp->next;
	}
	if (handle_redir(data, word) == -1)
		return (-1);
	return (0);
}
