/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:07:23 by carlaugu          #+#    #+#             */
/*   Updated: 2025/04/17 11:02:29 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "utils.h"
# include "errors.h"

/* -------------------------------------------------------------------------- */
/*                            EXPAND AND QUOTES                               */
/* -------------------------------------------------------------------------- */
int	analyze_token_context(t_word **word, t_data *data);
int	build_new(t_data *data, char *bgn, char *end, int len);
int	expand_val_len(char **bgn, t_data *data);
int	expand_tilde(t_word **word, t_data *data);
int	exp_join_segment(t_data *data, char **ptr, int len, char *end);
int	get_expand_val(t_data *data, char **ptr, char **tmp);
int	handle_quotes(char **ptr, t_data *data);
int	handle_tokens(t_word *word, t_data *data, t_tree_node **node);
int	join_split_words(t_data *data, char **tmp, char *val);
int	rebuild_tword(t_data *data, t_word **word, char *tmp1);
//EXPAND  UTILS
char	**get_words(char const *s);
int	get_segment_len(char *bgn, char *end, t_data *data);
void	tmp_str_change(char **ptr, char **no_alnum, char *box, bool end);
void	reset_big_part_flags(t_data *data);
void	reset_small_part_flags(t_data *data);
//EXPAND CHECKERS FUNCTIONS
bool	has_delimiter(char *s);
bool	is_valid_dollar(char *s);
bool	is_valid_tilde(char *s);
char	*find_next_quote_and_parse(char *s, t_data *data);
char	*find_non_alnum(char *s);
#endif
