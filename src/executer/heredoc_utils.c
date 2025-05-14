/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:50:20 by carlaugu          #+#    #+#             */
/*   Updated: 2025/05/14 14:42:11 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execute.h"
#include "../../include/expand.h"

int	verify_quotes(char **eof, bool *quotes, t_data *data)
{
	*quotes = false;
	if (has_quotes(*eof))
	{
		*quotes = true;
		if (remove_quotes(eof, false, data, NULL) == -1)
			return (-1);
		free(data->tmp_tree_node_word->next->word);
		data->tmp_tree_node_word->next->word = NULL;
	}
	return (0);
}

int	build_heredoc_wrd(char *input, t_data *data)
{
	t_word	*last;
	t_word	*new;

	new = ft_calloc(sizeof(t_word), sizeof(char));
	if (!new)
		return (error_allocation(data));
	new->word = ft_strdup(input);
	if (!new->word)
		return (error_allocation(data));
	last = last_word(data->doc_word);
	if (last)
		last->next = new;
	else
		data->doc_word = new;
	return (0);
}

void	print_to_pipe(t_word *doc_word, int *fd)
{
	while (doc_word)
	{
		if (doc_word->word)
			ft_putstr_fd(doc_word->word, fd[1]);
		write(fd[1], "\n", 1);
		doc_word = doc_word->next;
	}
}

void	parent_handle(int *fd, t_data *data, pid_t pid, int status)
{
	close(fd[1]);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	signal(SIGINT, handle_signal);
	set_exit_status(&status, data);
	if (data->exit_status)
		return ;
}

void	handle_sign_child(int i)
{
	write (1, "\n", 1);
	if (i == SIGINT)
		g_global = SIGINT;
	rl_replace_line("", 0);
	close(STDIN_FILENO);
}
