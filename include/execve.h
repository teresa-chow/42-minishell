/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:45:01 by carlaugu          #+#    #+#             */
/*   Updated: 2025/03/06 11:22:26 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECVE_H
# define EXECVE_H

# include <stdlib.h>
# include <sys/wait.h>

# include "parse.h"
# include "utils.h"
# include "struct.h"

# include "../lib/libft/libft/libft.h"

char	*get_path(t_env_node *env);
int		exec(t_data *data);
/* -------------------------------------------------------------------------- */
/*                                Execve Utils                                */
/* -------------------------------------------------------------------------- */
int	free_arrays(char **wrd_arr, char **env_arr, int i);
char	**creat_wrd_arr(t_word *word);
char	**creat_env_arr(t_env_node *env);
#endif