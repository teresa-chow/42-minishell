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

#include "parse.h"

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
/*                            PARSER                                */
/* -------------------------------------------------------------------------- */
/*typedef struct s_word
{
	struct s_word	*next;
	char	*word;
	int		flags;
}	t_word;

typedef struct s_word_lst
{
	struct s_word_lst	*next;
	struct s_word		*word;
}	t_word_lst;*/ //TODO: needs review

/* -------------------------------------------------------------------------- */
/*                               SPECIAL CASES                                */
/* -------------------------------------------------------------------------- */
typedef struct s_expand
{
	char	*bfr;
	char	*mid;
	char	*aft;
	char	*buf;
	char	*extra;
	char	**arr;
	char	**words;
	char	no_alnum;
}	t_expand;

/* -------------------------------------------------------------------------- */
/*                                 GENERAL                                    */
/* -------------------------------------------------------------------------- */
typedef struct s_data
{
	t_env_node	*env;
	t_expand	*exp;
	char		*cd_path;
	int			exit_status;
}	t_data;

#endif
