/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:00:39 by tchow-so          #+#    #+#             */
/*   Updated: 2025/05/13 16:34:35 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/errors.h"
#include "../../include/utils.h"

int	err_syntax(char *token)
{
	print_fd (STDERR_FILENO, "minishell: syntax error near "
		"unexpected token `%s'\n", token);
	return (ERR_BI);
}

int	error_allocation(t_data *data)
{
	ft_putendl_fd("minishell: Cannot allocate memory", STDERR_FILENO);
	data->exit_status = ERR;
	return (-1);
}

int	command_not_found(char *token, t_data *data)
{
	write(STDERR_FILENO, "minishell: ", 11);
	write(2, token, ft_strlen(token));
	write(STDERR_FILENO, ": command not found\n", 20);
	data->exit_status = ERR_F;
	return (ERR_F);
}

int	no_file_or_dir(char *token, t_data *data, int i)
{
	print_fd(STDERR_FILENO, "minishell: %s: No such file or directory\n",
		token);
	if (i)
		data->exit_status = ERR;
	else
		data->exit_status = ERR_F;
	return (data->exit_status);
}

int	is_a_directory(char *token, t_data *data)
{
	print_fd(STDERR_FILENO, "minishell: %s: Is a directory\n", token);
	data->exit_status = ERR_X;
	return (-1);
}
