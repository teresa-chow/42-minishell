/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:45:01 by carlaugu          #+#    #+#             */
/*   Updated: 2025/03/20 17:30:08 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECVE_H
# define EXECVE_H

# include <stdlib.h>
# include <sys/wait.h>
#include <sys/stat.h>


# include "utils.h"
# include "../lib/libft/libft/libft.h"
# include "parse.h"

typedef	struct s_exec_data
{
	char	**env_path;
	char	**env_arr;
	char	**wrd_arr;
	char	*tmp;
	char	*input;
}	t_exec_data;

char	*get_path(t_env_node *env);
void	exec(t_data *data, t_word *word);

/* -------------------------------------------------------------------------- */
/*                                Execve Utils                                */
/* -------------------------------------------------------------------------- */
int	free_arrays(t_exec_data *inf, t_data *data, int i);
char	**creat_wrd_arr(t_word *word);
char	**creat_env_arr(t_env_node *env);

#endif