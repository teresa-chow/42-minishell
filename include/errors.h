/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:00:39 by tchow-so          #+#    #+#             */
/*   Updated: 2025/03/18 12:15:21 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

/* Bash error codes: 1-catch all error code; 2-builtin misuse; 12-cannot allocate memory;
126-cmd cannot execute; 127-cmd not found; 128-invalid argument to exit; 
130-script terminated by SIGINT; 255-exit status out of range */
# define ERR 1
# define ERR_BI 2
# define ERR_MEM 12
# define ERR_X 126
# define ERR_F 127
# define ERR_EXIT 128
# define ERR_INT 130
# define ERR_OOR 255

# include <unistd.h>

# include "parse.h"
# include "builtins.h"

/* -------------------------------------------------------------------------- */
/*                                      Errors                                */
/* -------------------------------------------------------------------------- */
int err_syntax(char *token);
int	error_allocation(t_data *data);
int	command_not_found(char *token, t_data *data);
int	no_file_or_directory(char *token, t_data *data);
int	is_a_directory(char *token, t_data *data);
int	access_error(char *token, t_data *data);
// int	wrong_export_sintax(char *inpt);

#endif