/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:09:43 by tchow-so          #+#    #+#             */
/*   Updated: 2025/04/01 15:37:07 by tchow-so         ###   ########.fr       */
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
void	free_word_lst(t_word_lst **word_lst);
void	free_words(t_word **word);
int	free_env_list(t_data *data, int i, t_env_node **lst);

/* =============================== ENV INIT ================================ */
int		init_env_lst(char **envp, t_data *data);

/* =============================== SET PATH ================================ */
char	**set_path(t_data *data);

#endif