/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:39:11 by carlaugu          #+#    #+#             */
/*   Updated: 2025/03/06 13:38:26 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../lib/libft/libft/libft.h"
# include "../lib/libft/ft_printf/ft_printf.h"
# include "parse.h"
# include <errno.h>

typedef struct s_env_node
{
	char	*var;
	struct s_env_node *next;
	struct s_env_node *prev;
}	t_env_node;

/* ================================== ECHO ================================== */
void	echo(t_word *input);
/* =================================== CD =================================== */
void	cd(t_word *input);
/* ================================== PWD =================================== */
void	pwd(void);
/* ================================= EXPORT ================================= */
void	export(t_word *word_lst, t_env_node **env_lst);
/* ================================= UNSET ================================== */
void	unset(t_env_node **env_lst, t_word *word_lst);
/* ================================== ENV =================================== */
void	sort_env(t_env_node *env_lst);
void	print_export(t_env_node *env_lst);
int	init_env_lst(char **envp, t_env_node **env_lst);
/* ================================== EXIT ================================== */

#endif
