/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_err2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-24 22:15:30 by carlaugu          #+#    #+#             */
/*   Updated: 2025-03-24 22:15:30 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/errors.h"
#include "../../include/utils.h"

int	access_error(char *token, t_data *data)
{
	print_fd(2, "minishell: %s: ", token);
	perror(NULL);
	data->exit_status = ERR_X;
	return (-1);
}

int	cd_error(char *token, t_data *data)
{
	print_fd(2, "minishell: cd: %s: ", token);
	perror(NULL);
	data->exit_status = 1;
	return (-1);
}

int	error_export_syntax(char *inpt, t_data *data)
 {

	print_fd(2, "minishell: export: `%s': not a valid identifier\n", inpt);
	data->exit_status = ERR;
 	return (0);
 }
 
 int	exit_error_many_args(t_data *data)
 {
	print_fd(2, "minishell: exit: too many arguments\n", NULL);
	data->exit_status = ERR;
	return (1);
 }

 int	exit_error_syntax(char *inpt, t_data *data)
 {
	print_fd(2, "minishell: exit: %s: numeric argument required\n", inpt);
	data->exit_status = ERR_BI;
	return (0);
 }