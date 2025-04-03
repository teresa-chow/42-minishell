#ifndef SPECIAL_CASES_H
#define SPECIAL_CASES_H



/* -------------------------------------------------------------------------- */
/*                                     EXPAND                                 */
/* -------------------------------------------------------------------------- */
int	expand(t_data *data, t_word *word);
//EXPAND UTILS
int	check_lst_exp(t_data *data, char *arg);
int	count_quotes(char *s);
int	find_expand(t_word *word, t_data *data);
int	get_exp_vars(char *arg, t_data *data);
int	get_var_val(t_data *data, int i, char **tmp);
int	get_extra_chars(t_data *data, char **tmp);
int	has_delimiter(char *arg);
int	join_with_space(t_data *data, char **to_free);
char	find_extra(char *arg);
char	first_char(char *arg);
char	*get_last_exp(char *arg);
char	*get_var_and_extra_chars(char *s, t_data *data);
char	**get_words(char const *s);
char	*join_three(char *s1, char *s2, char *s3);

#endif