/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_err3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:02:24 by carlaugu          #+#    #+#             */
/*   Updated: 2025/04/30 23:30:42 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expand.h"

int	error_open_dir(t_data *data)
{
	perror ("Cannot open current directory");
	data->exit_status = ERR;
	return (-1);
}

void	heredoc_error(char *token)
{
	print_fd(STDERR_FILENO, "minishell: warning: here-document "
		"delimited by end-of-file (wanted `%s')\n", token);
}
