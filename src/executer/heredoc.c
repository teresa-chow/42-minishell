/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 10:59:18 by tchow-so          #+#    #+#             */
/*   Updated: 2025/04/17 11:03:57 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/execute.h"
#include "../../include/utils.h"

//end of file will not expand (analyze heredoc prior to expansions), content will
//readline

int	redir_heredoc(t_data *data, t_word *word)
{
	char	*input;
	int	fd[2];
	char	*eof;
	t_word	*tmp;

	(void)eof;
	(void)data;
	tmp = word;
	input = NULL;
	while (tmp)
	{
		if (tmp->redir == HEREDOC)
		{
			pipe(fd);
			eof = tmp->next->word;
			input = readline("> ");
			while (input && ft_strcmp(eof, input))
			{
				ft_putstr_fd(input, fd[1]);
				write (fd[1], "\n", 1);
				free (input);
				input = readline("> ");
				// if (!input)
				// 	// write error message
			}
		}
		tmp = tmp->next;
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	return (0);
 }
