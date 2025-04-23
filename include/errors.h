/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:00:39 by tchow-so          #+#    #+#             */
/*   Updated: 2025/04/17 11:05:06 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

/* Bash error codes: 1-catch all error code; 2-builtin misuse;
126-cmd cannot execute; 127-cmd not found; 128-invalid argument to exit; 
130-script terminated by SIGINT; 255-exit status out of range */
# define ERR 1
# define ERR_BI 2
# define ERR_X 126
# define ERR_F 127
# define ERR_EXIT 128
# define ERR_INT 130
# define ERR_OOR 255

# include <unistd.h>

# include "parse.h"
# include "builtins.h"

int	err_syntax(char *token);
int     error_open_dir(t_data *data);
int	error_allocation(t_data *data);
int	command_not_found(char *token, t_data *data);
int	no_file_or_dir(char *token, t_data *data, int i);
int	is_a_directory(char *token, t_data *data);
int	access_error(char *token, t_data *data);
int	cd_error(char *token, t_data *data, int i);
int	error_export_syntax(char *inpt, t_data *data);
int	exit_error_many_args(t_data *data);
int	exit_error_syntax(char *inpt, t_data *data);

#endif