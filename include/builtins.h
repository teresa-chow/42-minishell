/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:39:11 by carlaugu          #+#    #+#             */
/*   Updated: 2025/03/12 11:36:39 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <errno.h>

# include "../lib/libft/libft/libft.h"
# include "../lib/libft/ft_printf/ft_printf.h"
# include "struct.h"

/* ======================== Builtins Utils ================================== */
t_env_node	*last_node(t_env_node *env_lst);
int	set_inf(char *word, t_ipt_inf *inf_arg);
char	find_sep(char *s);
/* ================================== ECHO ================================== */
void	echo(t_word *input);
/* =================================== CD =================================== */
void	cd(t_word *input);
/* ================================== PWD =================================== */
void	pwd(void);
/* ================================= EXPORT================================= */
void	export(t_data *data);
void	reset_inf(t_ipt_inf *inf);
void	sort_env(t_env_node *env_lst);
t_env_node	*sort_halfs(t_env_node *head);
/* ================================= UNSET ================================== */
void	unset(t_data * data);
/* ================================== ENV =================================== */
void	env_cmd(t_env_node *env);
/* ================================== EXIT ================================== */

#endif
