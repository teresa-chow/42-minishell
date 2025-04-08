#ifndef EXPAND_H
#define EXPAND_H

# include "utils.h"
# include "errors.h"

/* -------------------------------------------------------------------------- */
/*                            EXPAND AND QUOTES                               */
/* -------------------------------------------------------------------------- */
int	analyze_args(t_word *word, t_data *data);
//EXPAND EXTRA FUNCTIONS
char	*find_non_alnum(char *s);
char	**get_words(char const *s);
char	*get_next_qt(char *s, t_data *data);
int	get_len(char *bgn, char *end, t_data *data);
int	has_delimiter(char *s);
int	is_valid_dollar(char *s);
void	check_special_char(char *s, t_data *data);
void	reset_checkers(t_data *data);
void	update_quotes_exp_status(char *ptr, t_data *data);

#endif