#ifndef EXPAND_H
#define EXPAND_H

# include "utils.h"

/* -------------------------------------------------------------------------- */
/*                                     EXPAND                                 */
/* -------------------------------------------------------------------------- */
int	expand(t_data *data, t_word *word);
//EXPAND EXTRA FUNCTIONS
char	**get_words(char const *s);
char	*get_var_and_extra_chars(char *s, t_data *data);
char	*join_three(char *s1, char *s2, char *s3);
int	expand_dollar(t_data *data, char **tmp, int i);
int	find_expand(t_word *word, t_data *data);
int	get_after(t_data *data, char *arg);
int	get_before(char *arg, t_data *data);
int	get_extra_chars(t_data *data, char **tmp);
int	get_mid(char *arg, t_data *data);
int	get_var_val(t_data *data, int i, char **tmp);
int	has_delimiter(char *arg);
int	is_valid_mid(t_data *data);
int	join_with_space(t_data *data, char **to_free);
int	set_mid(t_data *data, char **tmp);
//EXPAND UTILS
char	find_extra_var_name(char *arg);
char	*get_last_exp(char *arg);
char	*get_valid_dollar(char*arg);
int	count_begin_quotes(char *s);
int	count_no_quotes(char *start, char *end);
int	count_end_quotes(char *s);
void	add_no_quotes(char *dst,char *start, char *end);

#endif