/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:09:43 by tchow-so          #+#    #+#             */
/*   Updated: 2025/03/06 15:46:35 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include "../lib/libft/libft/libft.h"
# include "../lib/libft/ft_printf/ft_printf.h"
# include "builtins.h"
# include "parse.h"

typedef	struct s_ipt_inf
{
	char	*key;
	char	*val;
	char	sep;
	int	val_strt;
}	t_ipt_inf;

/* =========================== MEMORY MANAGEMENT =========================== */
void	free_strarray(char **array);
void	free_word_lst(t_word_lst *word_lst);
void	free_words(t_word **word);
void	free_env_list(t_env_node *lst);

#endif