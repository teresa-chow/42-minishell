/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:45:01 by carlaugu          #+#    #+#             */
/*   Updated: 2025/04/29 17:46:55 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECVE_H
# define EXECVE_H

# include <stdlib.h>
# include <sys/wait.h>
# include <sys/stat.h>

# include "utils.h"
# include "../lib/libft/libft/libft.h"
# include "parse.h"

typedef struct s_exec_data
{
	char	**path_splited;
	char	**env_arr;
	char	**wrd_arr;
	char	*tmp;
	char	*input;
}	t_exec_data;

int		exec_external(t_data *data, t_word *word);
int		free_arrays(t_exec_data *inf, t_data *data, int i);
int		find_slash(char *word);
char	**create_wrd_arr(t_word *word);
char	**create_env_arr(t_env_node *env);
void	free_failed_child(t_exec_data *inf, t_data *data);

#endif