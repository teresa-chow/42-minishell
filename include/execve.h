/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:45:01 by carlaugu          #+#    #+#             */
/*   Updated: 2025/03/18 12:13:24 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECVE_H
# define EXECVE_H

# include <stdlib.h>
# include <sys/wait.h>

# include "../lib/libft/libft/libft.h"
# include "utils.h"


char	*get_path(t_env_node *env);
int	exec(t_data *data, t_word *word);
/* -------------------------------------------------------------------------- */
/*                                Execve Utils                                */
/* -------------------------------------------------------------------------- */
int	free_arrays(char **wrd_arr, char **env_arr, int i);
char	**creat_wrd_arr(t_word *word);
char	**creat_env_arr(t_env_node *env);

#endif