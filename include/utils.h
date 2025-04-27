/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:09:43 by tchow-so          #+#    #+#             */
/*   Updated: 2025/04/27 21:44:26 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "parse.h"
# include "builtins.h"
# include "execute.h"
# include "struct.h"

# include "../lib/libft/libft/libft.h"
# include "../lib/libft/ft_printf/ft_printf.h"

/* Global variable */
extern int	global;

/* =============================== PRINT TO FD ============================== */
void	print_fd(int fd, const char *msg, char *token);

/* =========================== MEMORY MANAGEMENT =========================== */
void	reset_mem(t_data *data, t_tree_node **root);
void	free_strarray(char **array);
void	free_prompt(t_prompt *prompt);
void	free_word_lst(t_word_lst **word_lst);
void	free_w_lst_words(t_word_lst **word_lst);
void	free_words(t_word **word);
void	free_ast(t_tree_node **root);
int		free_env_list(t_data *data, int i, t_env_node **lst);
int		free_exp(t_data *data, int i);
void	free_pipeline(t_pipeline *pipeline);

/* =============================== ENV INIT ================================ */
int		init_env_lst(char **envp, t_data *data);

/* =============================== SET PATH ================================ */
char	**set_path(t_data *data, int *i);

/* ================================ GENERAL ================================ */
void	add_chars(char *start, char *end, char *dst);
int		handle_with_home(t_data *data);
char	*join_three(char *s1, char *s2, char *s3);

#endif