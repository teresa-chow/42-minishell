/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_err3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:02:24 by carlaugu          #+#    #+#             */
/*   Updated: 2025/04/30 11:36:53 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expand.h"

int    error_open_dir(t_data *data)
{
        perror ("Cannot open current directory");
	data->exit_status = 1;
	return (-1);
}

void	heredoc_error(char *token)
{
	print_fd(STDERR_FILENO, "minishell: warning: here-document "
	"delimited by end-of-file (wanted `%s')\n", token);
}