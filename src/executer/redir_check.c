/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 09:57:22 by carlaugu          #+#    #+#             */
/*   Updated: 2025/04/17 11:03:58 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/execute.h"
#include "../../include/errors.h"
#include "../../include/utils.h"

static int	handle_redir(t_data *data, t_word *word);
static int	check_redir_in(t_word *word, t_data *data);
static int	check_redir_out(t_word *word, t_data *data);

int redir_in_out_check(t_word *word, t_data *data)
{
	t_word	*tmp;
	int	i;

	if (!word)
		return (0);
	i = 0;
	tmp = word;
	while (tmp)
	{
		if (tmp->redir != NONE && tmp->next)
		{
			if (tmp->redir == IN)
				i = check_redir_in(tmp->next, data);
			if (tmp->redir == OUT || tmp->redir == APPEND)
				i = check_redir_out(tmp->next, data);
			if (i != 0)
			{
				data->redir_in = false;
				data->redir_out = false;
				return (-1);
			}
		}
		tmp = tmp->next;
	}
	return (handle_redir(data, word));
}

static int	handle_redir(t_data *data, t_word *word)
{
	int	i;

	i = 0;
	if (data->redir_in)
		i = redir_in(word, data);
	if (data->redir_out)
		i = redir_out(data, word);
	data->redir_in = false;
	data->redir_out = false;
	return (i);
}

static int	check_redir_in(t_word *word, t_data *data)
{
	data->redir_in = true;
	if (!access(word->word, F_OK))
	{
		if (access(word->word, R_OK) == -1)
		{
			print_fd(STDERR_FILENO, "minishell: %s: ", word->word);
			perror("");
			data->exit_status = 1;
			return (-1);
		}
	}
	else
		return (no_file_or_dir(word->word, data, 1), 1);
	return (0);
}

static int	check_redir_out(t_word *word, t_data *data)
{
	data->redir_out = true;
	if (!access(word->word, F_OK))
	{
		if (access(word->word, W_OK) < 0)
		{
			print_fd(STDERR_FILENO, "minishell: %s: ", word->word);
			perror("");
			data->exit_status = 1;
			return (-1);
		}
	}
	return (0);
}
