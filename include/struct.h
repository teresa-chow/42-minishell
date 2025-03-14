/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strcuts.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-14 15:59:24 by carlaugu          #+#    #+#             */
/*   Updated: 2025-03-14 15:59:24 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
#define STRUCTS_H

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

/* -------------------------------------------------------------------------- */
/*                            Parser Structs                                  */
/* -------------------------------------------------------------------------- */
typedef struct s_word
{
	struct s_word	*next;
	char	*word;
	int		flags;
}	t_word;

typedef struct s_word_lst
{
	struct s_word_lst	*next;
	struct s_word		*word;
}	t_word_lst;
/* -------------------------------------------------------------------------- */
/*                           Export and env init                              */
/* -------------------------------------------------------------------------- */
typedef	struct s_ipt_inf
{
	char	*key;
	char	*val;
	char	sep;
	int	val_strt;
}	t_ipt_inf;
/* -------------------------------------------------------------------------- */
/*                                 General                                    */
/* -------------------------------------------------------------------------- */
typedef struct	s_data
{
	// char	**envp;
	t_env_node *env;
	char	**cmd_lst;
	char	**env_path;
	// int	error_code
}	t_data;
#endif