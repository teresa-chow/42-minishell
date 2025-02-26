/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so  <tchow-so@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 21:49:05 by tchow-so          #+#    #+#             */
/*   Updated: 2025/02/15 21:49:05 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>

# include "../lib/libft/libft/libft.h"

enum	e_flags
{
	NONE = 0,
	VAR = 1,
	OPT = 2,
	LIT = 3,
	EXP = 4,
	EOF_FLAG = 5,
	ERR = 6,
	SPECIAL = 7 // commands fall in this cat
};

/* The basic data structure the bash shell uses to pass information from one
stage to the next, and to operate on data units within each processing stage,
is the WORD_DESC */
typedef struct s_word_desc
{
	char	*word;
	int		flags;
}	t_word_desc;

/* A command is a word list, the result of expansion is a word list, and the
built-in commands each take a word list of argumenst */
typedef struct s_word_list
{
	struct s_word_list	*next;
	struct s_word_desc	*word;
	
}	t_world_list;

// Input processing
void	read_input(void);
char	*get_path(char **envp);
// Tokenizer
char	**tokenizer(const char *input);

#endif
