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
int	analyze_token_context(t_word **word, t_data *data);
char	**get_words(char const *s);
int	build_new(t_data *data, char *bgn, char *end, int len);
int	expand_tilde(t_word **word, t_data *data);
int	get_var_val(t_data *data, char **ptr, char **tmp);
int	get_total_len(char *bgn, char *end, t_data *data);
int	join_normal_and_expansion(t_data *data, char **ptr, int len, char *end);
int	analyze_token_context(t_word **word, t_data *data);
void	join_splited_words(t_data *data, char **tmp);
void	reset_big_part_flags(t_data *data);
//EXPAND  UTILS
void	temp_string_change(char **ptr, char **inval, char *box, bool end);
//EXPAND CHECKERS FUNCTIONS
bool	is_valid_tilde(char *s);
char	*find_next_quote_and_parse(char *s, t_data *data);
char	*find_non_alnum(char *s);
int	has_delimiter(char *s);
int	is_valid_dollar(char *s);

#endif
