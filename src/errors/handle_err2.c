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
/*
int	wrong_export_sintax(char *inpt)
 {
 	char	*tmp;
 	char	*tmp1;

 	tmp = ft_strjoin("minishell: export: `", inpt);
 	if (!tmp)
 		return(error_allocation());
 	tmp1 = ft_strjoin(tmp, "': not a valid identifier");
 	free(tmp);
 	if (!tmp1)
 		return (error_allocation());
 	ft_putendl_fd(tmp1, 2);
 	return (0);
 }
 */