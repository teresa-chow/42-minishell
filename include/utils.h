/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:09:43 by tchow-so          #+#    #+#             */
/*   Updated: 2025/04/03 10:48:10 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "parse.h"
# include "builtins.h"
# include "struct.h"

# include "../lib/libft/libft/libft.h"
# include "../lib/libft/ft_printf/ft_printf.h"

/* =============================== PRINT TO FD ============================== */
void	print_fd(int fd, const char *msg, char *token);

/* =========================== MEMORY MANAGEMENT =========================== */
void	free_strarray(char **array);
void	free_word_lst(t_word_lst **word_lst, t_data *data);
void	free_words(t_word **word, t_data *data);
void	free_to_exit(t_data *data, t_word_lst **word_lst);
void	free_prompt(t_prompt *prompt);;
// void	free_many(char **s1, char **s2, char **s3);
int		free_env_list(t_data *data, int i, t_env_node **lst);
int		free_exp(t_data *data, t_word *word, int i);
/* =========================== ENV INIT =========================== */
int		init_env_lst(char **envp, t_data *data);
/* =========================== SET PATH =========================== */
char	**set_path(t_data *data, int *i);
/* =========================== GENERAL UTILS =========================== */
void	add_chars(char *start, char *end, char *dst);
int	handle_with_home(t_data *data);

#endif