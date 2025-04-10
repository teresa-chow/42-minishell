/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:07:23 by carlaugu          #+#    #+#             */
/*   Updated: 2025/04/10 16:38:44 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "utils.h"
# include "errors.h"

/* -------------------------------------------------------------------------- */
/*                            EXPAND AND QUOTES                               */
/* -------------------------------------------------------------------------- */
int		analyze_args(t_word *word, t_data *data);
//EXPAND EXTRA FUNCTIONS
char	*find_non_alnum(char *s);
char	**get_words(char const *s);
char	*get_next_qt(char *s, t_data *data);
int	build_new(t_data *data, char *bgn, char *end, int len);
int	expand_tilde(t_word **word, t_data *data);
int	get_var_val(t_data *data, char **ptr, char **tmp);
int	get_len(char *bgn, char *end, t_data *data);
int	has_delimiter(char *s);
int	is_valid_dollar(char *s);
int	join_normal_and_expansion(t_data *data, char **ptr, int len, char *end);
int	analyze_token_context(t_word **word, t_data *data);
void	join_splited_words(t_data *data, char **tmp);
void	reset_checkers(t_data *data);
void	update_quotes_exp_status(char *ptr, t_data *data);

#endif
