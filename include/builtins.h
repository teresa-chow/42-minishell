/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:39:11 by carlaugu          #+#    #+#             */
/*   Updated: 2025/03/18 12:22:58 by carlaugu         ###   ########.fr       */
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
void	echo(t_word *input, t_data *data);

/* =================================== CD =================================== */
void		cd(t_word *input, t_data *data);

/* ================================== PWD =================================== */
void	pwd(t_data *data);
/* ================================= EXPORT================================= */
void		export(t_data *data, t_word_lst *word_lst);
void		reset_inf(t_input_inf *inf);
void		sort_env(t_data *data);
t_env_node	*sort_halfs(t_env_node *head);
/* ================================= UNSET ================================== */
void		unset(t_data *data, t_word_lst *word_lst);

/* ================================== ENV =================================== */
void	env_cmd(t_env_node *env, t_data *data);

/* ================================== EXIT ================================== */

/* ============================== GENERAL UTILS ============================= */
int			set_inf(char *word, t_input_inf *inf_arg);
t_env_node	*last_node(t_env_node *env_lst);
t_env_node	*get_var(t_env_node *tmp, char *key);

#endif
