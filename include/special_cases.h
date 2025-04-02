/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_cases.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:29:41 by carlaugu          #+#    #+#             */
/*   Updated: 2025/04/02 15:30:18 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPECIAL_CASES_H
#define SPECIAL_CASES_H

/* -------------------------------------------------------------------------- */
/*                                     EXPAND                                 */
/* -------------------------------------------------------------------------- */
int		find_expand(t_word *word, t_data *data);
char	*get_last_exp(char *arg);
char	find_no_alnum(char *arg);
char	**get_words(char const *s);
int		expand(t_data *data, t_word *word);

#endif