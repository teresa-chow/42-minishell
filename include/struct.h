/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:59:24 by carlaugu          #+#    #+#             */
/*   Updated: 2025/04/27 11:17:43 by tchow-so         ###   ########.fr       */
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

/* 
- in_dbl and in_sing--> to know if we are inside quotes and how to handle
- to_exp--> to know if we can expand only if is a valid dollar sign and 
	if we are not inside single quotes
- to_split--> used to split data.exp.new_string when there are no quotes
	and it's not an export value expansion
- export_has_equal--> this, check if when we are in export builtin if 
	has equal signal must be treated as a literal
- export_exp_bfr_equal--> this check is we have an expansion before equal,
	to know if we have to split the var value and create new node
*/
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
	bool	to_split;
	bool	til_aft_equal;
	bool	export_cmd;
	bool	export_has_equal;
	bool	export_exp_bfr_equal;
}	t_expand;

/*
- wild_word is used to create a temp t_word with 
	new values to append to the original t_word
*/
typedef	struct s_wildcard
{
	bool	bgn;
	bool	mid;
	bool	end;
	bool	bgn_ok;
	bool	mid_ok;
	bool	end_ok;
	bool	print_dir;
	struct	s_word	*wild_word;
}	t_wildcard;


/* -------------------------------------------------------------------------- */
/*                                 GENERAL                                    */
/* -------------------------------------------------------------------------- */

/*
- redin_in and redir_out used to check if has redir
- no_home to know if we have home env or not
- exp used to handle with expansions
*/
typedef struct s_data
{
	bool	status;
	t_env_node	*env;
	t_expand	*exp;
	t_wildcard	*wild;
	struct s_word	**word;
	char		*env_home_var;
	int			exit_status;
	bool	no_home;
	bool	redir_in;
	bool	redir_out;
}	t_data;

#endif
