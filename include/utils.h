/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so  <tchow-so@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:09:43 by tchow-so          #+#    #+#             */
/*   Updated: 2025/02/27 12:09:43 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>

# include "parse.h"

/* =========================== MEMORY MANAGEMENT =========================== */
void	free_strarray(char **array);
void	free_word_lst(t_word_lst *word_lst);
void	free_words(t_word **word);

#endif