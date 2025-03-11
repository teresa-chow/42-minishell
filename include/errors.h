/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so  <tchow-so@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:00:39 by tchow-so          #+#    #+#             */
/*   Updated: 2025/03/11 11:00:39 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

/* Bash error codes: 1-catch all error code; 2-builtin misuse; 126-cmd cannot
execute; 127-cmd not found; 128-invalid argument to exit; 130-script terminated
by SIGINT; 255-exit status out of range */
# define ERR 1
# define ERR_BI 2
# define ERR_X 126
# define ERR_F 127
# define ERR_EXIT 128
# define ERR_INT 130
# define ERR_OOR 255

/* -------------------------------------------------------------------------- */
/*                                      Errors                                */
/* -------------------------------------------------------------------------- */
int	error_allocation(void);
// int	wrong_export_sintax(char *inpt);

#endif