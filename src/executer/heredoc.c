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
	(void)data;
	(void)word;
	/*char		*input;

	if (isatty(STDOUT_FILENO))
		input = readline("> ");
	else
		input = readline(NULL);
	if (input && *input)
	{
		//heredoc processing
	}
	if (input)
		free(input);*/
	return (0);
}