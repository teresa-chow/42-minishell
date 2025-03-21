/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 21:49:05 by tchow-so          #+#    #+#             */
/*   Updated: 2025/03/21 18:20:04 by tchow-so         ###   ########.fr       */
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
# include <unistd.h>

# include "struct.h"

# include "../lib/libft/libft/libft.h"
# include "../lib/libft/ft_printf/ft_printf.h"

typedef struct s_word
{
	struct s_word		*next;
	char				*word;
}	t_word;

typedef struct s_word_lst
{
	struct s_word_lst	*next;
	struct s_word		*word;
}	t_word_lst;

typedef enum	e_type
{
	CMD,
	GROUP, //will always execute in a subprocess: changes in directory will not affect current shell
	EXP,
	REDIR,
	PIPE,
	AND,
	OR
};

typedef struct s_tree_node
{
	int					index;
	enum e_type			type;
	t_word				*word;
	struct s_tree_node	*left;
	struct s_tree_node	*right;
}	t_tree_node;

/* =========================== INPUT PROCESSING ============================= */
void			read_input(t_tree_node **tree, t_data *data);

/* ==================== TOKENIZE: turn input into tokens ==================== */
char			**tokenize_op(char *input);
void			tokenize_w_lst(char **cmd_lst, t_word_lst *word_lst);
// Tokenize utils
unsigned int	group_len(const char *str, unsigned int start);
int				handle_parentheses(char *cmd, int *j, t_word_lst **word_lst,
					t_word **word);
int				handle_redirection(char *cmd, int *j, t_word_lst **word_lst,
					t_word **word);
int				handle_other(char *cmd, int *j, t_word_lst **word_lst,
					t_word **word);
int				handle_quote(char *cmd, int *j, t_word_lst **word_lst,
					t_word **word);
unsigned int	next_quote(const char *str, unsigned int start, int code);
int				init_word(t_word_lst *word_lst, t_word **word);
int				add_word(t_word **word_desc);
int				add_word_lst(t_word_lst **word_lst);
// Syntax utils
int				is_operator(int c);
int				is_delimiter(int c);
int				is_quote(int c);
int				is_redirection(int c);
//int			is_special(int c);
//int			is_unhandled(int c);
int				is_equal_next(const char *str, int i);

/* ============================ SYNTAX ANALYSIS ============================ */
int				syntax_analysis(t_word_lst *word_lst);
// Syntax analysis utils
int				check_logical_op(t_word *word);
int				check_op_syntax(char *word);
int				check_redir_seq(t_word_lst *word_lst, t_word *word);
int				is_valid_redir(t_word *word);
// Abstract Syntax Tree (AST)
void			create_syntax_tree(t_word_lst *word_lst, t_tree_node **root);
t_tree_node		*add_node(int index, t_word *word);

#endif

/* A command is a word list, the result of expansion is a word list, and the
built-in commands each take a word list of arguments */