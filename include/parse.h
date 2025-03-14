/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 21:49:05 by tchow-so          #+#    #+#             */
/*   Updated: 2025/03/12 11:17:52 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <stdbool.h>
# include <errno.h>

# include "../lib/libft/libft/libft.h"
# include "../lib/libft/ft_printf/ft_printf.h"
# include "struct.h"

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

/* =========================== INPUT PROCESSING ============================= */
void	read_input(t_data *data, t_word_lst *word_lst);

/* ==================== TOKENIZE: turn input into tokens ==================== */
char	**tokenize_op(char *input);
int		tokenize_w_lst(char **cmd_lst, t_word_lst *word_lst);
// Utils
int		is_operator(int c);
int		is_delimiter(int c);
int		is_quote(int c);
int		is_equal_next(const char *str, int i);
int		is_special(int c);
int		is_unhandled(int c);
unsigned int	group_len(const char *str, unsigned int start);
int 	handle_parentheses(char *cmd, int *j, t_word_lst **word_lst,
			t_word **word);
int		handle_other(char *cmd, int *j, t_word_lst **word_lst, t_word **word);
int		init_word(t_word_lst *word_lst, t_word **word);
int		handle_quote(char *cmd, int *j, t_word_lst **word_lst, t_word **word);
unsigned int	next_quote(const char *str, unsigned int start, int	code);
int		add_word(t_word **word_desc);
int		add_word_lst(t_word_lst **word_lst);

#endif

/* A command is a word list, the result of expansion is a word list, and the
built-in commands each take a word list of arguments */