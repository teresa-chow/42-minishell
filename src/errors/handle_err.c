/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:00:39 by tchow-so          #+#    #+#             */
/*   Updated: 2025/03/20 16:33:04 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/errors.h"
#include "../../include/utils.h"

int	err_syntax(char *token)
{
	print_fd (2, "minishell: syntax error near unexpected token `%s'\n",
		token);
	return (ERR_BI);
}

int	error_allocation(t_data *data)
{
	ft_putendl_fd("minishell: Cannot allocate memory", 2);
	data->exit_status = ERR;
	return (-1);
}

int	command_not_found(char *token, t_data *data)
{
	print_fd(2, "%s: command not found\n", token);
	data->exit_status = ERR_F;
	return (ERR_F);
}

int	no_file_or_directory(char *token, t_data *data)
{
	print_fd(2, "minishell: %s: No such file or directory\n", token);
	data->exit_status = ERR_F;
	return (ERR_F);
}

int	is_a_directory(char *token, t_data *data)
{
	print_fd(2, "minishell: %s: Is a directory\n", token);
	data->exit_status = ERR_X;
	return (-1);
}
