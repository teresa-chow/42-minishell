/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:07:23 by carlaugu          #+#    #+#             */
/*   Updated: 2025/05/14 15:03:59 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include <dirent.h>
# include <sys/stat.h>

# include "utils.h"
# include "errors.h"

/* ================== LITERAL AND EXPANDED VAR HANDLING ==================== */
int		analyze_token_context(t_word **word, t_data *data);
int		build_new(t_data *data, char *bgn, char *end, int len);
int		expand_val_len(char **bgn, t_data *data);
int		expand_tilde(t_word **word, t_data *data);
int		exp_join_segment(t_data *data, char **ptr, int len, char *end);
int		get_expand_val(t_data *data, char **ptr, char **tmp);
int		handle_quotes(char **ptr, t_data *data);
int		handle_tokens(t_word *word, t_data *data, t_tree_node **node);
int		join_split_words(t_data *data, char **tmp, char *val);
int		rebuild_tword(t_data *data, t_word **word, char *tmp1);

/* ========================= VAR EXPANSION UTILS =========================== */
char	**get_words(char const *s);
int		remove_quotes(char **str, bool to_free, t_data *data);
int		process_remove_quotes(t_word *word, t_data *data);
int		get_segment_len(char *bgn, char *end, t_data *data);
void	tmp_str_change(char **ptr, char **no_alnum, char *box, bool end);
void	reset_big_part_flags(t_data *data);
void	reset_small_part_flags(t_data *data);
// Checkers
bool	has_delimiter(char *s);
bool	is_valid_dollar(char *s);
bool	is_valid_tilde(char *s);
char	*find_next_quote_and_parse(char *s, t_data *data);
char	*find_non_alnum(char *s);
void	check_builtin_name(t_data *data, t_word **word);

/* ============================== WILDCARDS ================================ */
int		create_word_node(char *name, t_data *data);
int		free_wild(t_data *data, int i, DIR *dir);
int		handle_ast_quotes(char **ast_p, char *pat, char **tmp, t_data *data);
int		handle_wildcard(t_word *word, t_data *data);
int		is_matching_pattern(char *pat, char *name, t_data *data);
int		check_directory(struct dirent *entry, char *s, bool *check,
			t_data *data);
int		has_only_ast(char *s);
int		has_quotes(char *s);
int		match_mid(char *pat, char *last_ast, char *name, t_data *data);
int		verify_match(t_data *data);
char	*find_first_no_ast(char *s);
char	*get_last_ast(char *s);
char	*match_begin(char *pat, char *name, t_data *data);
char	*match_end(char *pat, char *name, t_data *data);
char	*next_ast(char *s);
t_word	*last_word(t_word *tmp_word);
void	find_substr(char **name, char *tmp, int *i);
void	update_tword(t_data *data, t_word **word, t_word *last);
void	reset_bool(t_data *data);
void	reset_data(t_data *data, bool *build_new);

#endif
