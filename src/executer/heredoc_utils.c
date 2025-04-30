/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:50:20 by carlaugu          #+#    #+#             */
/*   Updated: 2025/04/30 19:02:53 by tchow-so         ###   ########.fr       */
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
		if (remove_quotes(eof, false, data) == -1)
			return (-1);
	}
	return (0);
}

int	build_heredoc_wrd(t_word **doc_word, char *input, t_data *data)
{
	t_word	*last;
	t_word	*new;

	new = ft_calloc(sizeof(t_word), sizeof(char));
	if (!new)
		return (error_allocation(data));
	new->word = ft_strdup(input);
	if (!new->word)
		return (error_allocation(data));
	last = last_word(*doc_word);
	if (last)
		last->next = new;
	else
		*doc_word = new;
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
