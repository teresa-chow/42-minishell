/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:59:24 by carlaugu          #+#    #+#             */
/*   Updated: 2025/04/01 13:46:22 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

/* Structs associated with parsing can be found in parse.h header file */
#include "parse.h"

/* =========================== EXPORT + ENV INIT =========================== */
typedef struct s_input_inf
{
	int		val_strt;
	char	*key;
	char	*val;
	char	sep;
}	t_input_inf;

/* ================================== ENV ================================== */
typedef struct s_env_node
{
	char				*key;
	char				*val;
	struct s_env_node	*next;
	struct s_env_node	*prev;
}	t_env_node;

typedef struct s_env_init
{
	t_env_node	*oldpwd;
	t_env_node	*tmp;
	t_env_node	*last;
	t_input_inf	inf;
}	t_env_init;

/* =============================== EXPANDER ================================ */
typedef struct s_expand
{
	char	*bfr;
	char	*mid;
	char	*aft;
	char	*invalid_str;
	char	*buf;
	char	*extra;
	char	**arr;
	char	**words;
	char	no_alnum;
	int	invalid_pos;
}	t_expand;

/* ================================ GENERAL ================================ */
typedef struct s_data
{
	t_env_node	*env;
	t_expand	*exp;
	char		*home_path;
	int			exit_status;
}	t_data;

#endif
