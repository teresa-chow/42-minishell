#ifndef TEST_H
# define TEST_H

# include "../include/builtins.h"
# include "../include/execve.h"
# include "../include/parse.h"
# include "../include/utils.h"

void	test_builtins(t_word_lst *word_lst, t_env_node **env_lst, t_data *data);
void	print_word_lst(t_data *data, t_word_lst *word_lst);

#endif