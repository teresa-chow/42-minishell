/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:59:24 by carlaugu          #+#    #+#             */
/*   Updated: 2025/03/20 16:33:04 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
#define STRUCTS_H

/* -------------------------------------------------------------------------- */
/*                           Export and env init                              */
/* -------------------------------------------------------------------------- */
typedef	struct s_input_inf
{
	char	*key;
	char	*val;
	char	sep;
	int	val_strt;
}	t_input_inf;

/* -------------------------------------------------------------------------- */
/*                               Env Struct                                   */
/* -------------------------------------------------------------------------- */
typedef struct s_env_node
{
	char	*key;
	char	*val;
	struct s_env_node *next;
	struct s_env_node *prev;
}	t_env_node;


typedef struct s_env_init
{
	t_env_node	*oldpwd;
	t_env_node	*tmp;
	t_env_node	*last;
	t_input_inf	inf;
}	t_env_init;

/* -------------------------------------------------------------------------- */
/*                            Parser Structs                                  */
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
/*                                 General                                    */
/* -------------------------------------------------------------------------- */
typedef struct	s_data
{
	t_env_node *env;
	int	exit_status;
}	t_data;
#endif