/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:39:11 by carlaugu          #+#    #+#             */
/*   Updated: 2025/04/30 16:16:59 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <errno.h>

# include "parse.h"
# include "struct.h"

# include "../lib/libft/libft/libft.h"
# include "../lib/libft/ft_printf/ft_printf.h"

/* ================================== ECHO ================================== */
void		echo(t_word *input, t_data *data);

/* =================================== CD =================================== */
void		cd(t_word *input, t_data *data);

/* ================================== PWD =================================== */
void		pwd(t_data *data);

/* ================================= EXPORT================================= */
void		export(t_data *data, t_word *word);
void		reset_inf(t_input_inf *inf);
void		sort_env(t_data *data);
void		handle_with_args(t_word *word, t_data *data, int *exit);
t_env_node	*sort_halves(t_env_node *head);
int			add_var(t_input_inf *inf_arg, t_data *data);

/* ================================= UNSET ================================== */
void		unset(t_data *data, t_word *word);

/* ================================== ENV =================================== */
void		env_cmd(t_env_node *env, t_data *data);

/* ================================== EXIT ================================== */
void		exit_cmd(t_data *data, t_word *word);
long		exit_atol(t_word *word, t_data *data, int *syntax);

/* ============================== GENERAL UTILS ============================= */
int			set_inf(char *word, t_input_inf *inf_arg);
t_env_node	*last_node(t_env_node *env_lst);
t_env_node	*ft_getenv(t_env_node *env, char *key);

#endif
