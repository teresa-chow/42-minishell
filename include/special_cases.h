#ifndef SPECIAL_CASES_H
#define SPECIAL_CASES_H

/* -------------------------------------------------------------------------- */
/*                                     EXPAND                                 */
/* -------------------------------------------------------------------------- */
int	check_special_cases(t_data *data, t_word_lst *word_lst);
int	analyze_arg(char *arg, t_data *data);
void	expand(t_data *data, t_word *word);

#endif