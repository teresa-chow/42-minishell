/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:59:24 by carlaugu          #+#    #+#             */
/*   Updated: 2025/04/09 18:17:09 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

/* Structs associated with parsing can be found in parse.h header file */
# include "parse.h"

/* -------------------------------------------------------------------------- */
/*                           EXPORT AND ENV INIT                              */
/* -------------------------------------------------------------------------- */
typedef struct s_input_inf
{
	int		val_strt;
	char	*key;
	char	*val;
	char	sep;
}	t_input_inf;

/* -------------------------------------------------------------------------- */
/*                            ENV STRUCT                                      */
/* -------------------------------------------------------------------------- */
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

/* -------------------------------------------------------------------------- */
/*                                EXPANDER                                    */
/* -------------------------------------------------------------------------- */
typedef struct s_expand
{
	char	*new;
	char	**words;
	bool	in_dbl;
	bool	in_sing;
	bool	to_exp;
	bool	has_exp;
	bool	has_sing;
	bool	has_dbl;
}	t_expand;

/* -------------------------------------------------------------------------- */
/*                                 GENERAL                                    */
/* -------------------------------------------------------------------------- */
typedef struct s_data
{
	t_env_node	*env;
	t_expand	*exp;
	char		*home_path;
	int			exit_status;
}	t_data;

#endif
