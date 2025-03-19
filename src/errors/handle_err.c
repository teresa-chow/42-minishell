/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so  <tchow-so@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:00:39 by tchow-so          #+#    #+#             */
/*   Updated: 2025/03/11 11:00:39 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/errors.h"
#include "../../include/utils.h"

int err_syntax(char *token)
{
	print_fd(2, "minishell: syntax error near unexpected token `%s'\n", 
		token);
	return (ERR_BI);
}

int	error_allocation(t_data *data)
{
	ft_putendl_fd("minishell: Cannot allocate memory", 2);
	data->error_code = ERR_MEM;
	return (ERR_MEM);
}

int	command_not_found(char *token, t_data *data)
{
	print_fd(2, "%s: command not found\n", token);
	data->error_code = ERR_F;
	return (ERR_F);
}

int	no_file_or_directory(char *token, t_data *data)
{
	print_fd(2, "minishell: %s: No such file or directory\n", token);
	data->error_code = ERR_F;
	return (ERR_F);

}

int	is_a_directory(char *token, t_data *data)
{
	print_fd(2, "minishell: %s: Is a directory\n", token);
	data->error_code = ERR_X;
	return (-1);
}

int	access_error(char *token, t_data *data) 
{
	print_fd(2, "minishell: %s: ", token);
	perror(NULL);
	data->error_code = ERR_X; // confirm if is the corret code
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