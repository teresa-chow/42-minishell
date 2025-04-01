#ifndef SPECIAL_CASES_H
#define SPECIAL_CASES_H



/* -------------------------------------------------------------------------- */
/*                                     EXPAND                                 */
/* -------------------------------------------------------------------------- */
int	find_expand(t_word *word, t_data *data);
char	*get_last_exp(char *arg);
char	find_no_alnum(char *arg);
int	expand(t_data *data, t_word *word);

#endif