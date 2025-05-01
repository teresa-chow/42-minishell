/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 09:57:22 by carlaugu          #+#    #+#             */
/*   Updated: 2025/05/01 11:20:23 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/execute.h"
#include "../../include/errors.h"
#include "../../include/utils.h"

static int	handle_redir(t_data *data, t_word *word, bool in, bool out);
static int	check_redir_in(t_word *word, t_data *data, bool *in);
static int	check_redir_out(t_word *word, t_data *data, bool *out);

int	redir_in_out_check(t_word *word, t_data *data)
{
	t_word	*tmp;
	bool	in;
	bool	out;
	int		i;

	i = 0;
	in = false;
	out = false;
	if (!word)
		return (0);
	tmp = word;
	while (tmp)
	{
		if (tmp->redir != NONE && tmp->next)
		{
			if (tmp->redir == IN)
				i = check_redir_in(tmp->next, data, &in);
			if (tmp->redir == OUT || tmp->redir == APPEND)
				i = check_redir_out(tmp->next, data, &out);
			if (i != 0)
				return (-1);
		}
		tmp = tmp->next;
	}
	return (handle_redir(data, word, in, out));
}

static int	handle_redir(t_data *data, t_word *word, bool in, bool out)
{
	int	i;

	i = 0;
	if (in)
		i = redir_in(word, data);
	if (out)
		i = redir_out(data, word);
	return (i);
}

static int	check_redir_in(t_word *word, t_data *data, bool *in)
{
	*in = true;
	if (!access(word->word, F_OK))
	{
		if (access(word->word, R_OK) == -1)
		{
			print_fd(STDERR_FILENO, "minishell: %s: ", word->word);
			perror("");
			data->exit_status = ERR;
			return (-1);
		}
	}
	else
		return (no_file_or_dir(word->word, data, 1), 1);
	return (0);
}

static int	check_redir_out(t_word *word, t_data *data, bool *out)
{
	*out = true;
	if (!access(word->word, F_OK))
	{
		if (access(word->word, W_OK) < 0)
		{
			print_fd(STDERR_FILENO, "minishell: %s: ", word->word);
			perror("");
			data->exit_status = ERR;
			return (-1);
		}
	}
	return (0);
}
